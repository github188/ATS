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
        const char *ptr = addr;
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
    else if (dev->type == DT_SIM_CAMERA)
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
    osa_err_t       err;
    
    //err = osa_mutex_trylock(&dev_bus->mutex);
    
    for (l = dev_bus->ele_list_head.next; l != &dev_bus->ele_list_head; l = l->next)
    {
        node = osa_list_entry(l, ats_device_t, list);
        if (!strcmp(node->name, name))
        {
            return node;
        }
    }
    
    if (err == OSA_ERR_OK)
    {
        //osa_mutex_unlock(&dev_bus->mutex);
    }

    return NULL;
}

osa_err_t   ats_device_register(ats_bus_t *dev_bus, ats_device_t *dev)
{
    ats_device_t *p = NULL;

    //osa_err_t err = osa_mutex_lock(&dev_bus->mutex);

    if ((p = ats_device_find(dev_bus, dev->name)) != NULL)
    {
        ats_log_warn("Replace Device : name(%s)\n", dev->name);
        p = dev;
    }
    else
    {
        ats_log_info("Register device : name(%s), type(%d), addr(%s), user(%s), password(%s)\n",
                     dev->name, dev->type, dev->info.addr.addr, dev->info.user, dev->info.passwd);
        osa_list_insert_before(&dev_bus->ele_list_head, &dev->list);
    }

    //osa_mutex_unlock(&dev_bus->mutex);
    
    return OSA_ERR_OK;
}

osa_err_t ats_device_unregister(ats_bus_t         *dev_bus, 
                                const osa_char_t  *dev_name)
{
    osa_assert(dev_name != NULL);

    ats_device_t *p = NULL;

    if ((p = ats_device_find(dev_bus, dev_name)) != NULL)
    {
        ats_log_info("Unregister device : name(%s)\n", p->name);
        
        osa_list_remove(&p->list);
        if (p->remove)
        {
            p->remove(p);
        }
    }

    return OSA_ERR_OK;
}

osa_err_t ats_device_load_tdrv(ats_device_t     *dev, 
                               const osa_char_t *tdrv_file)
{
    osa_assert(tdrv_file != NULL);
    
    dev->drv = ats_tdrv_new(tdrv_file);
    if (!dev->drv)
    {
        ats_log_error("Failed to new test driver object!\n");
        return OSA_ERR_ERR;
    }
    
    dev->drv->dev = dev;
    
    extern osa_err_t xml_parse_drvfile(ats_tdrv_t *tdrv);
    
    return xml_parse_drvfile(dev->drv);
}

osa_err_t ats_device_load_sdk(ats_device_t      *dev, 
                              const osa_char_t  *sdk_plugin)
{
    osa_assert(sdk_plugin != NULL);
    
    typedef ats_sdk_t *(*sdk_get)(void);

    ats_sdk_t   *sdk = NULL;
    void        *p = NULL;
    sdk_get     getsdk = NULL;
    osa_dll_t   dll;
    
    if (osa_dll_load(&dll, sdk_plugin) != OSA_ERR_OK)
    {
        ats_log_error("Failed to load sdk plugin:%s\n", sdk_plugin);
        return OSA_ERR_ERR;
    }

    if ((p = osa_dll_sym(&dll, "SDK_PluginGet")) == NULL)
    {
        ats_log_error("Can not find the entry for sdk plugin: %s\n", sdk_plugin);
        osa_dll_unload(&dll);
        return OSA_ERR_ERR;
    }

    getsdk = (sdk_get)p;

    sdk = getsdk();
    osa_assert(sdk != NULL);
            
    dev->sdk = sdk;
    dev->sdk->dev = dev;
    strncpy(sdk->sdk_plugin, sdk_plugin, OSA_NAME_MAX-1);
    dev->sdk->dll.handler = dll.handler;
    
    ats_log_info("Load sdk(%s) for device (%s)!\n", sdk->sdk_plugin, dev->name);
    
    return OSA_ERR_OK;
}

void ats_device_unload_tdrv(ats_device_t *dev)
{
    if (dev->drv)
    {
        ats_tdrv_delete(dev->drv);
    }
    dev->drv = NULL;
}

void ats_device_unload_sdk(ats_device_t *dev)
{
    if (dev->sdk)
    {
        if (dev->sdk->SDK_exit)
        {
            dev->sdk->SDK_exit();
            ats_log_info("Unload sdk from device(%s)!\n", dev->name);
        }
        osa_dll_unload(&dev->sdk->dll);
    }
}

void ats_device_print(ats_device_t *dev)
{
    char *drv_file = (dev->drv)? dev->drv->drv_file : NULL;
    char *sdk_plugin = (dev->sdk) ? dev->sdk->sdk_plugin : NULL;
    
    printf("---------------------device----------------------\n");
    printf(" name       : %s\n", dev->name);
    printf(" type       : %d\n", dev->type);
    printf(" addr       : %s\n", dev->info.addr.addr);
    printf(" user       : %s\n", dev->info.user);
    printf(" password   : %s\n", dev->info.passwd);
    printf(" drv_file   : %s\n", drv_file);
    printf(" sdk_plugin : %s\n", sdk_plugin);
    printf("------------------------------------------------\n\n");
}

static void _def_dev_remove(ats_device_t *self)
{
    ats_log_info("Remove device : name(%s)\n", self->name);

    ats_device_delete(self);
}