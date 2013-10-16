/**
 *  osa_msg.h
 *
 */


#ifndef __OSA_MSG_H__
#define __OSA_MSG_H__


#include "osa_types.h"
#include "osa_error.h"
#include "osa_config.h"
#include "osa_ioch.h"


#ifdef __cplusplus
extern "C"
{
#endif


#define  MSG_CMD_LEN_MAX    32

typedef struct _OSA_MSG_HEADER
{
    osa_uint32_t    id;                     // message id
    osa_char_t      cmd[MSG_CMD_LEN_MAX];    // command
    osa_err_t       result;                 // result
    osa_size_t      data_size;               // content length
} osa_msgheader_t;


typedef struct _OSA_MSG
{
    osa_msgheader_t header;
    void            *data;
} osa_msg_t;


#define OSA_MSG_SEND_SIZE(msg)  (sizeof(osa_msgheader_t) + (msg)->header.data_size)


OSA_API osa_msg_t   *osa_msg_new();
OSA_API osa_msg_t   *osa_msg_new_ex(osa_uint32_t    id,
                                    osa_char_t      *cmd, 
                                    void            *data, 
                                    osa_size_t      size);
OSA_API void        osa_msg_delete(osa_msg_t *msg);

OSA_API void        osa_msg_set_result(osa_msg_t *msg, osa_err_t result);

OSA_API void        osa_msg_init(osa_msg_t      *msg, 
                                 osa_uint32_t   id, 
                                 osa_char_t     *cmd, 
                                 void           *data, 
                                 osa_size_t     size);
OSA_API void        osa_msg_fini(osa_msg_t *msg);

OSA_API osa_char_t  *osa_msg_pack(osa_msg_t *msg);
OSA_API osa_msg_t   *osa_msg_unpack(osa_char_t *str);

OSA_API void        osa_msg_dump(osa_msg_t *msg);

OSA_API osa_err_t   osa_msg_send(osa_ioch_t *ioch, osa_msg_t *msg);
OSA_API osa_err_t   osa_msg_recv(osa_ioch_t *ioch, osa_msg_t *out_msg);
OSA_API osa_err_t   osa_msg_send_recv(osa_ioch_t    *ioch,
                                      osa_msg_t     *sndmsg, 
                                      osa_msg_t     *out_rcvmsg, 
                                      osa_uint32_t  timeout_secs);

#ifdef __cplusplus
}
#endif

#endif
