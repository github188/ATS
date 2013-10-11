/**
 *  IPC_Onvif_prober.c
 *
 */


#include "osa.h"
#include "dev_prober.h"
#include "device.h"


void onvifProbe();


ATS_DevProber   onvifProber =
{
    .name   = "OnvifProber",
    .info = {
        .dp_class = 10,
    },
    .probe = onvifProbe,
};

void onvifProbe()
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
        ATS_Device *xmNetCamera = ATS_DeviceNew("XiongMai_NetCamera");
        ATS_DeviceSetInfo(xmNetCamera, "192.168.1.30", 34567, "admin", "");
        ATS_DevBusHangDev(xmNetCamera);
    }
}
