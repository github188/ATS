/**
 *  dev_bus.c
 *
 */


#include "osa.h"
#include "dev_bus.h"
#include "log.h"


// 设备总线
static ATS_DevBus   devBus;


static osa_err_t   devMatch(ATS_Device *dev, ATS_TestDrv *drv);
static osa_err_t   devRemove(ATS_Device *dev);
static osa_err_t   drvRemove(ATS_TestDrv *drv);

osa_err_t   ATS_DevBusInit()
{
    devBus.match = devMatch;

    osa_list_init(&devBus.devListHead);
    osa_list_init(&devBus.drvListHead);

    return OSA_ERR_OK;
}


ATS_DevBus  *ATS_DevBusGet()
{
    return &devBus;
}


ATS_Device  *ATS_DevBusFindDev(const osa_char_t *dev_name)
{
    osa_assert(dev_name != NULL);

    ATS_Device   *node = NULL;
    osa_list_t  *l = NULL;

    for (l = devBus.devListHead.next; l != &devBus.devListHead; l = l->next)
    {
        node = osa_list_entry(l, ATS_Device, list);

        // 找到
        if (!strcmp(node->name, dev_name))
        {
            return node;
        }
    }

    return NULL;
}


osa_err_t   ATS_DevBusHangDev(ATS_Device *dev)
{
    if (!dev)
    {
        return OSA_ERR_ERR;
    }

    ATS_Device   *p = NULL;

    ATS_LogInfo("Hang Device : name(%s)\n", dev->name);

    if ((p = ATS_DevBusFindDev(dev->name)) != NULL)
    {
        ATS_LogWarn("Replace Device : name(%s)\n", dev->name);
        p = dev;
    }
    else
    {
        osa_list_insert_before(devBus.devListHead.next, &dev->list);
    }

    ATS_TestDrv *node = NULL;
    osa_list_t  *l = NULL;

    for (l = devBus.drvListHead.next; l != &devBus.drvListHead; l = l->next)
    {
        node = osa_list_entry(l, ATS_TestDrv, list);
        // 调用匹配函数，匹配设备和对应的测试驱动
        if (devBus.match(dev, node) == OSA_ERR_OK)
        {
            dev->drv = node;
            break;
        }
    }
    if (l == &devBus.drvListHead)
    {
        ATS_LogInfo("No suitable driver for device : name(%s)\n", dev->name);
        return OSA_ERR_ERR;
    }
    else
    {
        ATS_LogInfo("Device: name(%s) / Driver: name(%s), conf_file(%s) matched\n", dev->name, node->name, node->cf);
        return OSA_ERR_OK;
    }

}


// 从总线上卸下设备
osa_err_t   ATS_DevBusUnhangDev(const osa_char_t *dev_name)
{
    osa_assert(dev_name != NULL);

    ATS_Device   *p = NULL;

    if ((p = ATS_DevBusFindDev(dev_name)) != NULL)
    {
        ATS_LogInfo("Unhang device: name(%s)!\n", dev_name);

        osa_list_remove(&p->list);
    }

    return OSA_ERR_OK;
}


ATS_TestDrv *ATS_DevBusFindDrv(const osa_char_t *drv_name)
{
    osa_assert(drv_name != NULL);

    ATS_TestDrv   *node = NULL;
    osa_list_t  *l = NULL;

    for (l = devBus.drvListHead.next; l != &devBus.drvListHead; l = l->next)
    {
        node = osa_list_entry(l, ATS_TestDrv, list);

        // 找到
        if (!strcmp(node->name, drv_name))
        {
            return node;
        }
    }

    return NULL;
}

osa_err_t   ATS_DevBusHangDrv(ATS_TestDrv *drv)
{
    if (!drv)
    {
        return OSA_ERR_ERR;
    }

    ATS_TestDrv   *p = NULL;

    ATS_LogInfo("Hang TestDriver : name(%s), conf_file(%s)\n", drv->name, drv->cf);

    if ((p = ATS_DevBusFindDrv(drv->name)) != NULL)
    {
        ATS_LogWarn("Replace driver: name(%s)\n", drv->name);
        p = drv;
    }
    else
    {
        osa_list_insert_before(devBus.drvListHead.next, &drv->list);
    }

    return OSA_ERR_OK;
}


osa_err_t   ATS_DevBusUnhangDrv(const osa_char_t *drv_name)
{
    osa_assert(drv_name != NULL);

    ATS_TestDrv *p = NULL;

    if ((p = ATS_DevBusFindDrv(drv_name)) != NULL)
    {
        ATS_LogInfo("Unhang TestDriver: name(%s)\n", drv_name);

        osa_list_remove(&p->list);
    }

    return OSA_ERR_OK;
}


osa_err_t   ATS_DevBusRemoveAllDev()
{
    ATS_Device   *node = NULL;
    osa_list_t  *l = NULL;

    for (l = devBus.devListHead.next; l != &devBus.devListHead; l = l->next)
    {
        node = osa_list_entry(l, ATS_Device, list);
        // 如果没有指定remove操作，则调用系统默认的操作
        if (!node->remove)
        {
            node->remove = devRemove;
        }

        if (node->remove(node) != OSA_ERR_OK)
        {
            ATS_LogError("Failed to remove device : name(%s)\n", node->name);
            continue;
        }
    }

    return OSA_ERR_OK;
}


osa_err_t   ATS_DevBusRemoveAllDrv()
{
    ATS_TestDrv *node = NULL;
    osa_list_t  *l = NULL;

    for (l = devBus.drvListHead.next; l != &devBus.drvListHead; l = l->next)
    {
        node = osa_list_entry(l, ATS_TestDrv, list);

        if (!node->remove)
        {
            node->remove = drvRemove;
        }

        if (node->remove(node) != OSA_ERR_OK)
        {
            ATS_LogError("Failed to remove TestDriver : name(%s)\n", node->name);
            continue;
        }
    }

    return OSA_ERR_OK;
}

static osa_err_t   devMatch(ATS_Device *dev, ATS_TestDrv *drv)
{
    // 根据设备和驱动的名字匹配
    if (!strcmp(dev->name, drv->name))
    {
        return OSA_ERR_OK;
    }

    return OSA_ERR_ERR;
}


static osa_err_t   devRemove(ATS_Device *dev)
{
    if (dev)
    {
        osa_mem_free(dev);
    }

    return OSA_ERR_OK;
}


static osa_err_t   drvRemove(ATS_TestDrv *drv)
{
    if (drv)
    {
        osa_mem_free(drv);
    }

    return OSA_ERR_OK;
}
