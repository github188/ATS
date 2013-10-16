/**
 *  osa_ioch.c
 *
 */
 
#ifndef __OSA_IOCH_H__
#define __OSA_IOCH_H__

#include "osa_types.h"
#include "osa_ioch.h"

#ifdef __cplusplus
extern "C"
{
#endif


OSA_API osa_err_t   osa_ioch_open(osa_ioch_t *ch, void *user_data)
{
}

OSA_API void        osa_ioch_close(osa_ioch_t *ch)
{
}

OSA_API osa_size_t  osa_ioch_write(osa_ioch_t   *ch, 
                                   osa_char_t   *data,
                                   osa_size_t   size)
{
}

OSA_API osa_size_t  osa_ioch_read(osa_ioch_t    *ch,
                                  osa_char_t    *data,
                                  osa_size_t    size)
{
}
OSA_API osa_err_t   osa_ioch_ctrl(osa_ioch_t    *ch,
                                  osa_int32_t   cmd,
                                  void          *param)
{
}

#ifdef __cplusplus
}
#endif

#endif