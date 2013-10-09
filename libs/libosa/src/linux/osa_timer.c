/**
 *  osa_timer.c
 *
 */


#include "osa_types.h"
#include "osa_timer.h"
#include "osa_select.h"
#include "osa_log.h"


void    osa_timer_delay(osa_uint32_t secs, osa_uint32_t msecs)
{
    osa_int32_t ret;
    struct timeval timeout;

    timeout.tv_sec = secs;
    timeout.tv_usec = msecs;

    ret = osa_select(0, NULL, NULL, NULL, &timeout);
    if (ret < 0)
    {
        osa_log_error("timer error!\n");
    }
}
