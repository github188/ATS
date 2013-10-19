/**
 *  osa_ioch.h
 *
 */


#ifndef __OSA_IOCH_H__
#define __OSA_IOCH_H__


#include "osa_types.h"
#include "osa_error.h"


#ifdef __cplusplus
extern "C"
{
#endif

typedef struct _OSA_IO_CHANNEL   osa_ioch_t;


struct _OSA_IO_CHANNEL
{
    osa_int32_t iofd;       // file descriptor
    void        *priv;      // private data
    osa_err_t   (*open)(osa_ioch_t *self, void *param);
    osa_err_t   (*close)(osa_ioch_t *self);
    osa_size_t  (*write)(osa_ioch_t *self,
                         osa_char_t *data,
                         osa_size_t size);
    osa_size_t  (*read)(osa_ioch_t *self,
                        osa_char_t *out_data,
                        osa_size_t size);
    osa_err_t   (*ioctrl)(osa_ioch_t     *self,
                          osa_int32_t    cmd,
                          void           *param);
};

OSA_API osa_err_t   osa_ioch_open(osa_ioch_t *ch, void *user_data);
OSA_API void        osa_ioch_close(osa_ioch_t *ch);
OSA_API osa_size_t  osa_ioch_write(osa_ioch_t   *ch,
                                   osa_char_t   *data,
                                   osa_size_t   size);
OSA_API osa_size_t  osa_ioch_read(osa_ioch_t    *ch,
                                  osa_char_t    *data,
                                  osa_size_t    size);
OSA_API osa_err_t   osa_ioch_ctrl(osa_ioch_t    *ch,
                                  osa_int32_t   cmd,
                                  void          *param);

#ifdef __cplusplus
}
#endif


#endif
