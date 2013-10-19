/**
 *  osa_signal.c 
 *
 */
 
#include "osa_types.h"
#include "osa_signal.h"

#include <signal.h>

void osa_signal_bind(osa_int32_t signum, sig_t handler)
{
    signal(signum, handler);
}

