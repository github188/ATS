/**
 *  IPC_Onvif_prober.c
 *
 */


#include "osa.h"
#include "core.h"
#include "module/dev_prober.h"


static osa_bool_t netcamera_dev_is_ok(ats_devinfo_t *devinfo);


ats_devpb_t netcamera_prober =
{
    .name   = "OnvifProber",
    .dev_support = "XM:DEV:NetCamera,TEST:DEV:DummyDev",
    .dev_is_ok = netcamera_dev_is_ok,
};

static osa_bool_t netcamera_dev_is_ok(ats_devinfo_t *devinfo)
{
    return OSA_TRUE;
}
