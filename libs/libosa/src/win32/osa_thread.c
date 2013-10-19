/**
 *  osa_thread.c
 *
 */


#include "osa_types.h"
#include "osa_error.h"
#include "osa_log.h"
#include "osa_thread.h"

#include <process.h>


osa_err_t osa_thread_init(osa_thread_t *t, osa_char_t *name, thread_entry entry, void *param)
{
    strncpy(t->name, name, OSA_NAME_MAX-1);

    t->entry = entry;
    t->param = param;

    return OSA_ERR_OK;
}

void osa_thread_exit()
{
    _endthread();
}

osa_err_t osa_thread_start(osa_thread_t *t)
{
    typedef void ( *entry_func )(void *);

    _beginthread((entry_func)t->entry, 0, t->param);

    return OSA_ERR_OK;
}


osa_err_t   osa_mutex_init(osa_mutex_t *mtx)
{
    mtx->mutex = CreateMutex(NULL, 0, "");
    if (mtx->mutex == 0)
    {
        return OSA_ERR_ERR;
    }
    return OSA_ERR_OK;
}

void        osa_mutex_fini(osa_mutex_t *mtx)
{
    CloseHandle(mtx->mutex);
}

osa_err_t   osa_mutex_lock(osa_mutex_t *mtx)
{
    DWORD ret = WaitForSingleObject(mtx->mutex, INFINITE);
    if (ret == WAIT_FAILED)
    {
        osa_log_error("mutex error!\n");
        return OSA_ERR_ERR;
    }
    return OSA_ERR_OK;
}

osa_err_t   osa_mutex_unlock(osa_mutex_t *mtx)
{
    ReleaseMutex(mtx->mutex);
	return OSA_ERR_OK;
}

osa_err_t   osa_mutex_trylock(osa_mutex_t *mtx)
{
    DWORD ret = WaitForSingleObject(mtx->mutex, 0);
    if (ret == WAIT_FAILED)
    {
        osa_log_error("mutex error!\n");
        return OSA_ERR_ERR;
    }
    return OSA_ERR_OK;
}

osa_err_t   osa_cond_init(osa_cond_t *cond)
{
    return OSA_ERR_ERR;
}

void        osa_cond_fini(osa_cond_t *cond)
{
    
}

osa_err_t   osa_cond_signal(osa_cond_t *cond)
{
    return OSA_ERR_ERR;
}

osa_err_t   osa_cond_wait(osa_cond_t     *cond, 
                          osa_timespec_t *timeout)
{
    return OSA_ERR_ERR;
}

