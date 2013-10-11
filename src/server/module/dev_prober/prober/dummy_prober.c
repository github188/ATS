/**
 *  dummy_prober.c
 *
 */


#include "osa.h"
#include "device.h"
#include "module/dev_prober.h"


void dummyDoProbe();


static ats_devprober_t   dummyProber =
{
    .name   = "dummyProber",
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
        ats_device_t *dummyDev = ats_device_new("dummyDev");
        ats_device_setinfo(dummyDev, "192.168.1.10", 34567, "admin", "");
    }
}
