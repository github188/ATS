/**
 *  osa_process.c
 *
 */


#include "osa_types.h"
#include "osa_process.h"
#include "osa_log.h"
#include "osa_error.h"
#include "osa_string.h"



osa_err_t   osa_process_init(osa_process_t *process, osa_char_t *name, process_entry entry, void *param)
{
    osa_assert(name != NULL);

    strncpy(process->name, name, OSA_NAME_MAX -1);
    process->entry = entry;
    process->param = param;
    process->pid = OSA_INVALID_PID;

	return OSA_ERR_OK;
}


osa_err_t   osa_process_start(osa_process_t *process)
{
    if (process->pid != OSA_INVALID_PID)
    {
        return OSA_ERR_ERR;
    }

    process->pid = fork();

    if (process->pid < 0)
    {
        return OSA_ERR_ERR;
    }
    else if (process->pid > 0)
    {
        close(process->pid);
        return OSA_ERR_OK;
    }
    else
    {
        if (process->entry)
        {
            process->entry(process->param);
        }
        return OSA_ERR_OK;
    }
}


void        osa_process_exit(osa_process_t *process)
{
    close(process->pid);
}
