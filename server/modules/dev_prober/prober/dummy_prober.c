/**
 *  dummy_prober.c
 *
 */


#include "osa.h"
#include "dev_prober.h"
#include "device.h"

void dummyDoProbe();

ATS_DevProber   dummyProber =
{
    .name   = "dummyProber",
    .info = {
        .dp_class = 10,
    },
    .probe = dummyDoProbe,
};

void dummyDoProbe()
{
    osa_bool_t devIsAlive = OSA_TRUE;

    if (devIsAlive != OSA_TRUE)
    {
        ATS_DevBusUnhangDev("dummyDev");
        return;
    }

    if (ATS_DevBusFindDev("dummyDev") != NULL)
    {
        return;
    }
    else
    {
        ATS_Device *dummyDev = ATS_DeviceNew("dummyDev");
        ATS_DeviceSetInfo(dummyDev, "192.168.0.100", 3000, "admin", "admin");
        ATS_DevBusHangDev(dummyDev);


        ATS_Device *dummyDev_none = ATS_DeviceNew("dummyDev_none");
        ATS_DeviceSetInfo(dummyDev_none, "192.168.0.200", 3000, "admin", "admin");
        ATS_DevBusHangDev(dummyDev_none);
    }
}
