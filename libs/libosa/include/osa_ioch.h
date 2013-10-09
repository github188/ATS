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
    osa_uint32_t    iofd;       // file descriptor
    void            *priv;      // private data
    osa_err_t       (*open)(osa_ioch_t *self, void *param);
    osa_err_t       (*close)(osa_ioch_t *self);
    osa_size_t      (*write)(osa_ioch_t *self, osa_char_t *data, osa_size_t size);
    osa_size_t      (*read)(osa_ioch_t *self, osa_char_t *out_data, osa_size_t size);
};


#ifdef __cplusplus
}
#endif


#endif
