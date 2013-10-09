/**
 *  osa_select.c
 *
 */


#include "osa_types.h"
#include "osa_select.h"
#include "osa_types.h"
#include "osa_log.h"

#include <sys/select.h>


osa_int32_t osa_select(osa_uint32_t maxfd, osa_fdset_t *rfds, osa_fdset_t *wfds, osa_fdset_t *efds, struct timeval *timeout)
{
    osa_int32_t ret = 0;

    ret = select(maxfd, rfds, wfds, efds, timeout);

    switch (ret)
    {
    case -1:
    {
        osa_log_error("Select error !\n");
        ret = OSA_SELECT_ERROR;
        break;
    }
    case 0:
    {
        ret = OSA_SELECT_TIMEOUT;
        break;
    }
    default:
    {
    }
    }

    return ret;
}
