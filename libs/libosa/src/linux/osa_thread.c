/**
 *  osa_thread.c
 *
 */

#include "osa_types.h"
#include "osa_thread.h"
#include "osa_error.h"
#include "osa_log.h"

#include <pthread.h>


osa_err_t   osa_thread_init(osa_thread_t *t, osa_char_t *name, thread_entry entry, void *param)
{
    strncpy(t->name, name, OSA_NAME_MAX-1);

    t->entry = entry;
    t->param = param;

    return OSA_ERR_OK;
}


void        osa_thread_exit(osa_thread_t *t)
{

}


osa_err_t   osa_thread_start(osa_thread_t *t)
{
    if (pthread_create(&t->tid, NULL, t->entry, t->param) != 0)
    {
        osa_log_error("Failed to start thread : %s!\n", t->name);
        return OSA_ERR_ERR;
    }
    return OSA_ERR_OK;
}


void        osa_thread_stop(osa_thread_t *t)
{

}