/**
 *  device.c
 *
 */


#include "osa.h"
#include "device.h"
#include "log.h"
#include "bus.h"
#include "test_drv.h"
#include "sdk.h"


static void _def_dev_remove(ats_device_t *self);


ats_device_t *ats_device_new(const osa_char_t *dev_name)
{
    osa_assert(dev_name != NULL);
    
    ats_device_t *dev = (ats_device_t *)osa_mem_alloc(sizeof(ats_device_t));

    strncpy(dev->name, dev_name, OSA_NAME_MAX-1);
    dev->sdk = NULL;
    dev->drv = NULL;
    dev->remove = _def_dev_remove;
    osa_list_init(&dev->list);

    return dev;
}


void ats_device_delete(ats_device_t *dev)
{
    if (dev)
    {
        osa_list_remove(&dev->list);
        osa_mem_free(dev);
    }
}


void ats_device_setinfo(ats_device_t *dev, 
                    const osa_char_t *ip, osa_uint32_t port, 
                    const osa_char_t *user, const osa_char_t *passwd)
{
    strncpy(dev->info.ip, ip, 19);
    strncpy(dev->info.user, user, 31);
    strncpy(dev->info.passwd, passwd, 31);
    dev->info.port = port;
}


ats_device_t  *ats_device_find(ats_bus_t *dev_bus, const osa_char_t *name)
{
    osa_assert(name != NULL);

    ats_device_t    *node   = NULL;
    osa_list_t      *l      = NULL;

    for (l = dev_bus->ele_list_head.next; l != &dev_bus->ele_list_head; l = l->next)
    {
        node = osa_list_entry(l, ats_device_t, list);
        if (!strcmp(node->name, name))
        {
            return node;
        }
    }
    
    return NULL;
}

osa_err_t   ats_device_register(ats_bus_t *dev_bus, ats_device_t *dev)
{
    ats_device_t *p = NULL;
    
    if ((p = ats_device_find(dev_bus, dev->name)) != NULL)
    {
        ats_log_warn("Replace Device : name(%s)\n", dev->name);
        p = dev;
    }
    else
    {
        ats_log_info("Register new device : name(%s)\n", dev->name);
        osa_list_insert_before(&dev_bus->ele_list_head, &dev->list);
    }
    
    /** find the driver */
    ats_bus_t *tdrv_bus = ats_bus_find("tdrv_bus");
    if (!tdrv_bus)
    {
        ats_log_error("no test driver bus found!\n");
    }
    
    ats_tdrv_t *node = NULL;
    osa_list_t *l = NULL;
    
    for (l=tdrv_bus->ele_list_head.next; l!=&tdrv_bus->ele_list_head; l=l->next)
    {
        node = osa_list_entry(l, ats_tdrv_t, list);
        if (tdrv_bus->ops->match)
        {
            if (tdrv_bus->ops->match(node, dev) == OSA_TRUE)
            {
                ats_log_info("Device matched driver!\n");
                dev->drv = node;
                break;
            }
        }
    }
    
    /** find the sdk */
    
    return OSA_ERR_OK;
}

osa_err_t   ats_device_unregister(ats_bus_t *dev_bus, const osa_char_t *dev_name)
{
    osa_assert(dev_name != NULL);
    
    ats_device_t *p = NULL;
    
    if ((p = ats_device_find(dev_bus, dev_name)) != NULL)
    {
        osa_list_remove(&p->list);
        if (p->remove)
        {
            p->remove(p);
        }
        ats_log_info("Unregister device : name(%s)\n", p->name);
    }
    
    return OSA_ERR_OK;
}

static void _def_dev_remove(ats_device_t *self)
{
    ats_log_info("Remove device : name(%s)\n", self->name);
    
    ats_device_delete(self);
}
