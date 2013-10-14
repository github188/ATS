/**
 *  IPC_Onvif_prober.c
 *
 */


#include "osa.h"
#include "core.h"
#include "module/dev_prober.h"


static osa_bool_t netcamera_dev_is_ok(ats_device_t *dev);


ats_devpb_t netcamera_prober =
{
    .name   = "OnvifProber",
    .dev_support = "XM:DEV:NetCamera",
    .dev_is_ok = netcamera_dev_is_ok,
};

static osa_bool_t netcamera_dev_is_ok(ats_device_t *dev)
{
	if (!strcmp(dev->info.addr.net_addr.ip, "192.168.1.30"))
	{
		return OSA_TRUE;
	}
	return OSA_FALSE;
}
