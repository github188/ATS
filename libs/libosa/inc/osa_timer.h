/**
 *  osa_timer.h
 *
 */


#ifndef __OSA_TIMER_H__
#define __OSA_TIMER_H__


#include "osa_types.h"


#ifdef __cplusplus
extern "C"
{
#endif


// delay : secs(seconds), msecs(micro seconds)
OSA_API void    osa_timer_delay(osa_uint32_t secs, osa_uint32_t msecs);


#ifdef __cplusplus
}
#endif


#endif

