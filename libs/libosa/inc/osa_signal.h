/**
 *  osa_signal.h
 *
 */
 
 
#ifndef __OSA_SIGNAL_H__
#define __OSA_SIGNAL_H__

#include "osa_types.h"

#ifdef __cplusplus
extern "C"
{
#endif


#include <signal.h>

typedef void(*sig_t)(osa_int32_t);

enum
{
    OSA_SIG_INT = SIGINT,
    OSA_SIG_TERM = SIGTERM,
};

OSA_API void    osa_signal_bind(osa_int32_t signum, sig_t handler);


#ifdef __cplusplus
}
#endif

#endif

