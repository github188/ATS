/**
 *  device.c
 *
 */


#include "ats.h"
#include "osa.h"
#include "device.h"
#include "log.h"



ATS_Device  *ATS_DeviceNew(const osa_char_t *devname)
{
    ATS_Device *dev = osa_mem_alloc(sizeof(ATS_Device));

    strncpy(dev->name, devname, OSA_NAME_MAX-1);
    dev->drv = NULL;

    osa_list_init(&dev->list);

    return dev;
}


void    ATS_DeviceDelete(ATS_Device *dev)
{
    if (dev)
    {
        osa_mem_free(dev);

        osa_list_remove(&dev->list);
    }
}

void    ATS_DeviceSetInfo(ATS_Device *dev, osa_char_t *ip, osa_uint32_t port, osa_char_t *user, osa_char_t *passwd)
{
    strncpy(dev->info.ip, ip, 19);
    strncpy(dev->info.user, user, 31);
    strncpy(dev->info.passwd, passwd, 31);
    dev->info.port = port;
}


void    ATS_DeviceTest(ATS_Device *dev)
{
    if (!dev->drv)
    {
        return;
    }

    ATS_LogInfo("Start test device : %s\n", dev->name);

    // 解析配置文件
    ATS_TestDrvParseConf(dev->drv);

    // 执行测试
    ATS_TestDrvDoTest(dev->drv);

}
