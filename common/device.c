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
    osa_assert(addr != NULL);

    strncpy(dev->info.addr.addr, addr, strlen(addr));

    // net camera, use  ip + port
    if (dev->type == DT_NET_CAMERA)
    {
        char ip[32] = {0};
        char port[32] = {0};
        char *ptr = addr;
        osa_uint8_t flag= 0;
        osa_uint32_t i=0;

        while (*ptr)
        {
            if (*ptr == ':')
            {
                flag = 1;
                ptr++;
                i=0;
                continue;
            }
            if (flag == 0)
            {
                ip[i++] = *ptr;
                ip[sizeof(ip)-1] = '\0';
            }
            else
            {
                port[i++] = *ptr;
                port[sizeof(port)-1] = '\0';
            }
            ptr++;
        }
        strncpy(dev->info.addr.net_addr.ip, ip, strlen(ip));
        dev->info.addr.net_addr.port = atoi(port);
    }
    // simulator camera, user CON. port
    else if (dev->type = DT_SIM_CAMERA)
    {
        strncpy(dev->info.addr.con_addr, addr, strlen(addr));
    }
    else
    {
        ats_log_error("Unknown device type!\n");
    }

    if (user)
    {
        strncpy(dev->info.user, user, strlen(user));
    }
    if (passwd)
    {
        strncpy(dev->info.passwd, passwd, strlen(passwd));
    }
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
        ats_log_info("Register new device : name(%s), type(%d), addr(%s), user(%s), password(%s)\n",
                     dev->name, dev->type, dev->info.addr.addr, dev->info.user, dev->info.passwd);
        osa_list_insert_before(&dev_bus->ele_list_head, &dev->list);
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
