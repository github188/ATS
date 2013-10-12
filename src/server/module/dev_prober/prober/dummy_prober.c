/**
 *  dummy_prober.c
 *
 */


#include "osa.h"
#include "device.h"
#include "bus.h"
#include "log.h"

#include "module/dev_prober.h"


void dummy_do_probe();


ats_devprober_t   dummy_prober =
{
    .name   = "dummyProber",
    .probe = dummy_do_probe,
};


void dummy_do_probe()
{
    osa_bool_t devIsAlive = OSA_TRUE;

    ats_bus_t   *devbus = ats_bus_find("dev_bus");
    if (!devbus)
    {
        ats_log_error("no device bus found!\n");
        return ;
    }
    
    if (devIsAlive != OSA_TRUE)
    {
        ats_device_unregister(devbus, "dummyDev");
        return;
    }

    if (ats_device_find(devbus, "dummyDev") != NULL)
    {
        return;
    }
    else
    {
        ats_device_t *dummy_dev = ats_device_new("dummyDev");
        ats_device_setinfo(dummy_dev, "192.168.1.10", 34567, "admin", "");
        
        ats_device_register(devbus, dummy_dev);
    }
}
