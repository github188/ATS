/**
 *  osa_thread.h
 *
 */


#ifndef __OSA_THREAD_H__
#define __OSA_THREAD_H__


#include "osa_types.h"
#include "osa_error.h"


#ifdef __OSA_OS_LINUX__
#include <pthread.h>
typedef pthread_t   osa_tid_t;
#define OSA_INVALID_TID     -1
#endif

#ifdef __OSA_OS_WIN32__
typedef HANDLE      osa_tid_t;
#define OSA_INVALID_TID     NULL
#endif


#ifdef __cplusplus
extern "C"
{
#endif


typedef void *(*thread_entry)(void *param);

typedef struct _OSA_THREAD
{
    osa_tid_t       tid;
    osa_char_t      name[OSA_NAME_MAX];     // name of task
    thread_entry    entry;                  // entry of task
    void            *param;                 // param
} osa_thread_t;


OSA_API osa_err_t   osa_thread_init(osa_thread_t *t, osa_char_t *name, thread_entry entry, void *param);
OSA_API void        osa_thread_exit(osa_thread_t *t);

OSA_API osa_err_t   osa_thread_start(osa_thread_t *t);
OSA_API void        osa_thread_stop(osa_thread_t *t);


#ifdef __cplusplus
}
#endif


#endif
