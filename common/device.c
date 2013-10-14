/**
 *  device.c
 *
 */


#include "osa.h"
#include "core.h"


static void _def_dev_remove(ats_device_t *self);


ats_device_t *ats_device_new(const osa_char_t *dev_name, ats_devtype_t type)
{
    osa_assert(dev_name != NULL);
    
    ats_device_t *dev = (ats_device_t *)osa_mem_alloc(sizeof(ats_device_t));

    strncpy(dev->name, dev_name, OSA_NAME_MAX-1);
    dev->type = type;
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


void ats_device_setinfo(ats_device_t *dev, const osa_char_t *addr,
                    const osa_char_t *user, const osa_char_t *passwd)
{
    // net camera, use  ip + port
    if (dev->type == DT_NET_CAMERA)
    {
        osa_char_t ipaddr[32] = {0};
		osa_char_t *ip = ipaddr;
        osa_char_t *port = NULL;
        
        osa_char_t *ptr = addr;
        while (*ptr)
        {
            if (*ptr == ':')
            {
                port = ptr++;
                break;
            }
            *(ip++) = *ptr;
        }
        
        strncpy(dev->info.addr.net_addr.ip, ipaddr, sizeof(dev->info.addr.net_addr.ip)-1);
        dev->info.addr.net_addr.port = atoi(port);
    }
    // simulator camera, user CON. port
    else if (dev->type = DT_SIM_CAMERA)
    {
        strncpy(dev->info.addr.con_addr, addr, sizeof(dev->info.addr.con_addr)-1);
    }

    strncpy(dev->info.user, user, 31);
    strncpy(dev->info.passwd, passwd, 31);
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
        ats_log_warn("No suitable test driver for device (%s)!\n", dev->name);
    }
    
    ats_bus_t *sdk_bus = ats_bus_find("sdk_bus");
    if (!sdk_bus)
    {
        ats_log_warn("No suitable sdk for device (%s)!\n", dev->name);
    }
    
    ats_tdrv_t *tdrv = NULL;
    ats_sdk_t  *sdk = NULL;
    osa_list_t *l = NULL;
    
    for (l=tdrv_bus->ele_list_head.next; l!=&tdrv_bus->ele_list_head; l=l->next)
    {
        tdrv = osa_list_entry(l, ats_tdrv_t, list);
        if (tdrv_bus->ops->match)
        {
            if (tdrv_bus->ops->match(tdrv, dev) == OSA_TRUE)
            {
                ats_log_info("Device matched driver: %s!\n", dev->name);
                dev->drv = tdrv;
				tdrv->dev = dev;
                break;
            }
        }
    }
    if (l == &tdrv_bus->ele_list_head)
    {
        ats_log_warn("No suitable test driver for device : %s\n", dev->name);
    }
    
    /** find the sdk */
    for (l=sdk_bus->ele_list_head.next; l!=&sdk_bus->ele_list_head; l=l->next)
    {
        sdk = osa_list_entry(l, ats_sdk_t, list);
        if (sdk_bus->ops->match)
        {
            if (sdk_bus->ops->match(sdk, dev) == OSA_TRUE)
            {
                ats_log_info("Device matched : %s!\n", dev->name);
                dev->sdk = sdk;
				sdk->dev = dev;
                break;
            }
        }
    }
    if (l == &sdk_bus->ele_list_head)
    {
        ats_log_warn("No suitable sdk for device : %s\n", dev->name);
    }
    
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
