/**
 *  IPC_Onvif_prober.c
 *
 */


#include "osa.h"
#include "device.h"
#include "log.h"
#include "module/dev_prober.h"


void onvif_do_probe();


ats_devprober_t onvif_prober =
{
    .name   = "OnvifProber",
    .probe = onvif_do_probe,
};

void onvif_do_probe()
{
    osa_bool_t dev_is_alive = OSA_TRUE;

    ats_bus_t   *devbus = ats_bus_find("dev_bus");
    if (!devbus)
    {
        ats_log_error("no xx bus found!\n");
        return ;
    }
    
    if (dev_is_alive != OSA_TRUE)
    {
        ats_device_unregister(devbus, "XiongMai_NetCamera");
        return;
    }

    if (ats_device_find(devbus, "XiongMai_NetCamera") != NULL)
    {
        return;
    }
    else
    {
        ats_device_t *xm_net_camera= ats_device_new("XiongMai_NetCamera");
        ats_device_setinfo(xm_net_camera, "192.168.1.30", 34567, "admin", "");

        ats_device_register(devbus, xm_net_camera);
    }
}
