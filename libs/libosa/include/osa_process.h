/**
 *  osa_process.h
 *
 */


#ifndef __OSA_RPOCESS_H__
#define __OSA_PROCESS_H__


#include "osa_types.h"
#include "osa_error.h"
#include "osa_config.h"


#ifdef __OSA_OS_LINUX__
#include <unistd.h>
typedef pid_t   osa_pid_t;
#define OSA_INVALID_PID     -1
#endif

#ifdef __OSA_OS_WIN32__
typedef HANDLE  osa_pid_t;
#define OSA_INVALID_PID     NULL
#endif

#ifdef __cplusplus
extern "C"
{
#endif


typedef void (*process_entry)(void *parameter);


typedef struct _OSA_TASK
{
    osa_pid_t   pid;
    osa_char_t  name[OSA_NAME_MAX];     // name of process
    process_entry  entry;                  // entry of process
    void        *param;                 // param
} osa_process_t;


OSA_API osa_err_t   osa_process_init(osa_process_t *process, osa_char_t *name, process_entry entry, void *param);
OSA_API osa_err_t   osa_process_start(osa_process_t *process);
OSA_API void        osa_process_exit(osa_process_t *process);

#ifdef __cplusplus
}
#endif


#endif
