/**
 *  IPC_Onvif_prober.c
 *
 */


#include "osa.h"
#include "dev_prober.h"
#include "device.h"


void IPC_OnvifDoProbe();


ATS_DevProber   IPCProber =
{
    .name   = "IPCProber",
    .info = {
        .dp_class = 10,
    },
    .probe = IPC_OnvifDoProbe,
};

void IPC_OnvifDoProbe()
{
}
