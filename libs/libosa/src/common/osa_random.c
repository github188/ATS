/**
 *  osa_random.c
 *
 */


#include "osa_types.h"
#include "osa_random.h"
#include "osa_time.h"


osa_int32_t     osa_rand_int32(osa_int32_t min, osa_int32_t max)
{
    osa_timeval_t tpstart;
    osa_double_t r;

    osa_time_gettimeofday(&tpstart);
    srand(tpstart.tv_usec);

    r = (rand()/(RAND_MAX + 1.0));

    return min + (osa_uint32_t )(r*(max - min));
}
