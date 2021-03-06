/**
 *  table.c
 *
 */


#include "osa.h"
#include "dev_prober.h"



#define DEV_PROBER(dp)  &dp

/**----------------------------------------*/
extern ATS_DevProber    dummyProber;
extern ATS_DevProber    IPCProber;


ATS_DevProber   *g_devProberTable[] =
{
    DEV_PROBER(dummyProber),
    DEV_PROBER(IPCProber),
};

osa_uint32_t g_devProberNum = sizeof(g_devProberTable)/sizeof(g_devProberTable[0]);