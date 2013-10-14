/**
 *  osa_select.h
 *
 */


#ifndef __OSA_SELECT_H__
#define __OSA_SELECT_H__


#include "osa_types.h"
#include "osa_time.h"


#ifdef __OSA_OS_LINUX__
#include <sys/socket.h>
#endif


#ifdef __cplusplus
extern "C"
{
#endif


#define    OSA_SELECT_ERROR         -1
#define    OSA_SELECT_TIMEOUT       0


typedef     fd_set      osa_fdset_t;


OSA_API osa_int32_t osa_select(osa_uint32_t maxfd,
                               osa_fdset_t *rfds,
                               osa_fdset_t *wfds,
                               osa_fdset_t *efds,
                               osa_timeval_t *timeout);


#ifdef __cplusplus
}
#endif

#endif
