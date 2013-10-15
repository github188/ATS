/**
 *  osa_thread.c
 *
 */

#include "osa_types.h"
#include "osa_thread.h"
#include "osa_error.h"
#include "osa_log.h"
#include "osa_string.h"
#include "osa_time.h"

#include <pthread.h>


osa_err_t   osa_thread_init(osa_thread_t *t, osa_char_t *name, thread_entry entry, void *param)
{
    strncpy(t->name, name, OSA_NAME_MAX-1);

    t->entry = entry;
    t->param = param;

    return OSA_ERR_OK;
}

void osa_thread_exit()
{
    pthread_exit(NULL);
}

osa_err_t osa_thread_start(osa_thread_t *t)
{
    if (pthread_create(&t->tid, NULL, t->entry, t->param) != 0)
    {
        osa_log_error("Failed to start thread : %s!\n", t->name);
        return OSA_ERR_ERR;
    }
    return OSA_ERR_OK;
}


osa_err_t osa_mutex_init(osa_mutex_t *mtx)
{
    if (pthread_mutex_init(&mtx->mutex, NULL) != 0)
    {
        return OSA_ERR_ERR;
    }
    return OSA_ERR_OK;
}

void osa_mutex_fini(osa_mutex_t *mtx)
{
    pthread_mutex_destroy(&mtx->mutex);
}

osa_err_t   osa_mutex_lock(osa_mutex_t *mtx)
{
    osa_int32_t ret = pthread_mutex_lock(&mtx->mutex);
    if (ret != 0)
    {
        return OSA_ERR_ERR;
    }
    return OSA_ERR_OK;
}

osa_err_t   osa_mutex_unlock(osa_mutex_t *mtx)
{
    if (pthread_mutex_unlock(&mtx->mutex) != 0)
    {
        return OSA_ERR_ERR;
    }
    return OSA_ERR_OK;
}

osa_err_t   osa_mutex_trylock(osa_mutex_t *mtx)
{
    osa_int32_t ret = pthread_mutex_trylock(&mtx->mutex);
    if (ret != 0)
    {
        return OSA_ERR_ERR;
    }
    return OSA_ERR_OK;
}

osa_err_t osa_cond_init(osa_cond_t *cond)
{
    if (pthread_cond_init(&cond->cond, NULL) != 0)
    {
        return OSA_ERR_ERR;
    }
    osa_mutex_init(&cond->mutex);
    return OSA_ERR_OK;
}

void osa_cond_fini(osa_cond_t *cond)
{
    osa_mutex_fini(&cond->mutex);
    pthread_cond_destroy(&cond->cond);
}

osa_err_t   osa_cond_signal(osa_cond_t *cond)
{
    osa_mutex_lock(&cond->mutex);
    
    pthread_cond_signal(&cond->cond);
    
    osa_mutex_unlock(&cond->mutex);
    
    return OSA_ERR_OK;
}

osa_err_t   osa_cond_wait(osa_cond_t *cond, osa_timespec_t *timeout)
{
    osa_mutex_lock(&cond->mutex);
    
    pthread_cond_timedwait(&cond->cond, &cond->mutex.mutex, timeout);
    
    osa_mutex_unlock(&cond->mutex);
    
    return OSA_ERR_OK;
}
