/**
 *  sys_bus.c 
 *
 */
 
 
#include "osa.h"
#include "bus.h"
#include "device.h"
#include "test_drv.h"
#include "sdk.h"


static ats_bus_t        dev_bus;
static ats_bus_ops_t    dev_bus_ops;
static ats_bus_t        tdrv_bus;
static ats_bus_ops_t    tdrv_bus_ops;
static ats_bus_t        sdk_bus;
static ats_bus_ops_t    sdk_bus_ops;



static osa_bool_t  tdrv_bus_match(void *bus_element, void *match_element);
static osa_bool_t  sdk_bus_match(void *bus_element, void *match_element);
static void        dev_bus_remove(ats_bus_t *bus);
static void        tdrv_bus_remove(ats_bus_t *bus);
static void        sdk_bus_remove(ats_bus_t *bus);


osa_err_t   system_bus_init()
{
    dev_bus_ops.match = NULL;
    dev_bus_ops.remove = dev_bus_remove; 
    ats_bus_register(&dev_bus, "dev_bus", &dev_bus_ops);
    
    tdrv_bus_ops.match = tdrv_bus_match;
    tdrv_bus_ops.remove = tdrv_bus_remove;
    ats_bus_register(&tdrv_bus, "tdrv_bus", &tdrv_bus_ops);
    
    sdk_bus_ops.match = sdk_bus_match;
    sdk_bus_ops.remove = sdk_bus_remove;
    ats_bus_register(&sdk_bus, "sdk_bus", &sdk_bus_ops);
    
    return OSA_ERR_OK;
}

void        system_bus_fini()
{
    
}


static osa_bool_t  tdrv_bus_match(void *bus_element, void *match_element)
{
    ats_device_t *dev = (ats_device_t *)match_element;
    ats_tdrv_t  *drv = (ats_tdrv_t *)bus_element;
    
    if (!strcmp(dev->name, drv->name))
    {
        return OSA_TRUE;
    }
    return OSA_FALSE;
}

static osa_bool_t  sdk_bus_match(void *bus_element, void *match_element)
{
    ats_device_t *dev = (ats_device_t *)match_element;
    ats_sdk_t  *sdk = (ats_sdk_t *)bus_element;
    
    if (!strcmp(dev->name, sdk->name_space))
    {
        return OSA_TRUE;
    }
    return OSA_FALSE;
}

static void        dev_bus_remove(ats_bus_t *bus)
{
    
}

static void        tdrv_bus_remove(ats_bus_t *bus)
{
}

static void        sdk_bus_remove(ats_bus_t *bus)
{
}