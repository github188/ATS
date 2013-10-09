/**
 *  osa_select.c
 *
 */

 

#include "osa_types.h"
#include "osa_select.h"
#include "osa_types.h"
#include "osa_log.h"
#include "osa_time.h"


osa_int32_t osa_select(osa_uint32_t maxfd, osa_fdset_t *rfds, osa_fdset_t *wfds, osa_fdset_t *efds, osa_timeval_t *timeout)
{
    osa_int32_t ret = 0;

    // in windows, the first parameter [maxfd] will be ignored
#ifdef __OSA_TOOL_MINGW32__
    ret = select(0, rfds, wfds, efds, (struct timeval *)timeout);
#else
    /** for msvc */
    ret = select(0, rfds, wfds, efds, (timeval *)timeout);
#endif

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
