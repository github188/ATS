/**
 *  osa_time.c
 *
 */


#include "osa_types.h"
#include "osa_error.h"
#include "osa_log.h"
#include "osa_time.h"



void    osa_time_gettimeofday(osa_timeval_t *out_tv)
{
    osa_uint64_t  intervals;
    FILETIME  ft;

    GetSystemTimeAsFileTime(&ft);

    intervals = ((osa_uint64_t)ft.dwHighDateTime << 32) | ft.dwLowDateTime;
    intervals -= 116444736000000000;

    out_tv->tv_sec = (long) (intervals / 10000000);
    out_tv->tv_usec = (long) ((intervals % 10000000) / 10);
}
