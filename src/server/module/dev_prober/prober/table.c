/**
 *  table.c
 *
 */


#include "osa.h"
#include "module/dev_prober.h"


#define DEV_PROBER(dp)  &dp

/**----------------------------------------*/
extern ats_devprober_t    dummy_prober;
extern ats_devprober_t    onvif_prober;


ats_devprober_t   *g_devProberTable[] =
{
    DEV_PROBER(dummy_prober),
    DEV_PROBER(onvif_prober),
};

osa_uint32_t g_devProberNum = sizeof(g_devProberTable)/sizeof(g_devProberTable[0]);
