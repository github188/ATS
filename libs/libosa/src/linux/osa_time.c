/**
 *  osa_time.c
 *
 */


#include "osa_types.h"
#include "osa_time.h"

#include <time.h>

void    osa_time_gettimeofday(osa_timeval_t *out_tv)
{
    gettimeofday(out_tv, NULL);
}