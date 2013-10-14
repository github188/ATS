/**
 *  table.c
 *
 */


#include "osa.h"
#include "module/dev_prober.h"


#define DEV_PROBER(dp)  &dp

/**----------------------------------------*/
extern ats_devpb_t    netcamera_prober;


ats_devpb_t   *g_dptable[] =
{
    DEV_PROBER(netcamera_prober),
};

osa_uint32_t g_dpnum = sizeof(g_dptable)/sizeof(g_dptable[0]);
