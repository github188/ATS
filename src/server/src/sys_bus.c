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



static void        dev_bus_remove(ats_bus_t *bus);



osa_err_t system_bus_init()
{
    dev_bus_ops.match = NULL;
    dev_bus_ops.remove = dev_bus_remove;
    ats_bus_register(&dev_bus, "dev_bus", &dev_bus_ops);

    return OSA_ERR_OK;
}

void system_bus_fini()
{
    dev_bus_remove(&dev_bus);
}


static void dev_bus_remove(ats_bus_t *bus)
{
    ats_device_t *node = NULL;
    osa_list_t *l = NULL;

    for (l=bus->ele_list_head.next; l!=&bus->ele_list_head; l=l->next)
    {
        node = osa_list_entry(l, ats_device_t, list);
        ats_device_unregister(bus, node->name);
    }
}
