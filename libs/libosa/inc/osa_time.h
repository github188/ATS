/**
 *  osa_time.h
 *
 */


#ifndef __OSA_TIME_H__
#define __OSA_TIME_H__


#include "osa_types.h"


#ifdef __cplusplus
extern "C"
{
#endif


#if (defined(__OSA_TOOL_MINGW32__) || defined(__OSA_TOOL_GNUC__))
typedef struct timeval  osa_timeval_t;
typedef struct timespec osa_timespec_t;
#else
typedef struct _timeval
{
    osa_uint32_t    tv_sec;
    osa_uint32_t    tv_usec;
} osa_timeval_t;
typedef struct _timespec
{
    osa_uint32_t    tv_sec;
    osa_uint32_t    tv_nsec;
} osa_timespec_t;
#endif

typedef osa_uint64_t    osa_time_t;


OSA_API void        osa_time_gettimeofday(osa_timeval_t *out_tv);


#ifdef __cplusplus
}
#endif

#endif
