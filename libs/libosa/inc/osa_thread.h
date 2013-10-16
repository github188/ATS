/**
 *  osa_thread.h
 *
 */


#ifndef __OSA_THREAD_H__
#define __OSA_THREAD_H__


#include "osa_types.h"
#include "osa_error.h"
#include "osa_time.h"


#ifdef __OSA_OS_LINUX__
#include <pthread.h>
typedef pthread_t       osa_tid_t;
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

/** thread */
typedef struct
{
    osa_tid_t       tid;
    osa_char_t      name[OSA_NAME_MAX];     // name of task
    thread_entry    entry;                  // entry of task
    void            *param;                 // param
} osa_thread_t;


OSA_API osa_err_t   osa_thread_init(osa_thread_t    *t,
                                    osa_char_t      *name, 
                                    thread_entry    entry, 
                                    void            *param);

OSA_API osa_err_t   osa_thread_start(osa_thread_t *t);
OSA_API void        osa_thread_exit();


/** mutex */
#ifdef __OSA_OS_LINUX__
typedef struct
{
    pthread_mutex_t mutex;
}osa_mutex_t;
#endif

#ifdef __OSA_OS_WIN32__
typedef struct
{
    HANDLE  mutex;
}osa_mutex_t;
#endif

OSA_API osa_err_t   osa_mutex_init(osa_mutex_t *mtx);
OSA_API void        osa_mutex_fini(osa_mutex_t *mtx);

OSA_API osa_err_t   osa_mutex_lock(osa_mutex_t *mtx);
OSA_API osa_err_t   osa_mutex_trylock(osa_mutex_t *mtx);
OSA_API osa_err_t   osa_mutex_unlock(osa_mutex_t *mtx);


/** condition */
#ifdef __OSA_OS_LINUX__
typedef struct
{
    pthread_cond_t  cond;
    osa_mutex_t     mutex;
}osa_cond_t;
#endif

#ifdef __OSA_OS_WIN32__
typedef struct
{
    HANDLE          cond;
    osa_mutex_t     mutex;
}osa_cond_t;
#endif

OSA_API osa_err_t   osa_cond_init(osa_cond_t *cond);
OSA_API void        osa_cond_fini(osa_cond_t *cond);

OSA_API osa_err_t   osa_cond_signal(osa_cond_t *cond);
OSA_API osa_err_t   osa_cond_wait(osa_cond_t        *cond, 
                                  osa_timespec_t    *timeout);

#ifdef __cplusplus
}
#endif


#endif
