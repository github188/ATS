/**
 *  IPC_Onvif_prober.c
 *
 */


#include "osa.h"
#include "device.h"
#include "module/dev_prober.h"


void onvif_probe();


ats_devprober_t onvifProber =
{
    .name   = "OnvifProber",
    .probe = onvif_probe,
};

void onvif_probe()
{
    osa_bool_t devIsAlive = OSA_TRUE;

    if (devIsAlive != OSA_TRUE)
    {
        ATS_DevBusUnhangDev("XiongMai_NetCamera");
        return;
    }

    if (ATS_DevBusFindDev("XiongMai_NetCamera") != NULL)
    {
        return;
    }
    else
    {
        ats_bus_t *devbus = ats_bus_find("dev_bus");
        if (!devbus)
        {
            ats_log_error("no device bus found!\n");
            return;
        }

        ats_device_t *xm_net_camera= ats_device_new("XiongMai_NetCamera");
        ats_device_setinfo(xm_net_camera, "192.168.1.30", 34567, "admin", "");

        ats_device_register(devbus, xm_net_camera);
    }
}
