/**
 *  osa_timer.c
 *
 */



#include "osa_types.h"
#include "osa_timer.h"
#include "osa_error.h"
#include "osa_log.h"


void    osa_timer_delay(osa_uint32_t secs, osa_uint32_t msecs)
{
    Sleep(secs*1000+msecs);
}
