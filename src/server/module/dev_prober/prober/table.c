/**
 *  table.c
 *
 */


#include "osa.h"
#include "module/dev_prober.h"



#define DEV_PROBER(dp)  &dp

/**----------------------------------------*/
extern ats_devprober_t    dummyProber;
extern ats_devprober_t    onvifProber;


ats_devprober_t   *g_devProberTable[] =
{
    DEV_PROBER(dummyProber),
    DEV_PROBER(onvifProber),
};

osa_uint32_t g_devProberNum = sizeof(g_devProberTable)/sizeof(g_devProberTable[0]);
