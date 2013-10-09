/**
 *  osa_error.h
 *
 */


#ifndef __OSA_ERROR_H__
#define __OSA_ERROR_H__


#include "osa_types.h"
#include "osa_log.h"


#ifdef __cplusplus
extern "C"
{
#endif

enum
{
    OSA_ERR_OK      = 0,
    OSA_ERR_ERR     = -1,
    OSA_ERR_NOMEM   = -10,
};


typedef osa_int32_t osa_err_t;


#define     osa_ret_if_fail(cond)     do { \
    if (!(cond)) { \
        osa_log_error("Return value check failed at <%s, %d>\n", __FILE__, __LINE__); \
        return; \
    } \
}while(0)


#define     osa_ret_val_if_fail(cond, retVal)  do { \
    if (!(cond)) { \
        osa_log_error("Return value check failed at <%s, %d>\n", __FILE__, __LINE__); \
        return (retVal); \
    } \
}while(0)


#define     osa_assert(cond)    do { \
    if (!(cond)) { \
        osa_log_error("Assert failed at <%s, %d>\n", __FILE__, __LINE__); \
        getchar(); \
    } \
}while(0)


#ifdef __cplusplus
}
#endif

#endif
