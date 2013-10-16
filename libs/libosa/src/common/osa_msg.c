/**
 *  osa_msg.c
 *
 */


#include "osa_types.h"
#include "osa_msg.h"
#include "osa_mem.h"
#include "osa_log.h"
#include "osa_error.h"
#include "osa_select.h"
#include "osa_string.h"
#include "osa_time.h"


#define MSGID_MIN   100
#define MSGID_MAX   5000


osa_msg_t   *osa_msg_new()
{
    osa_msg_t *p = (osa_msg_t *)osa_mem_alloc(sizeof(osa_msg_t));

    return p;
}

osa_msg_t   *osa_msg_new_ex(osa_uint32_t id, osa_char_t *cmd, void *data, osa_size_t size)
{
    osa_msg_t *p = (osa_msg_t* )osa_mem_alloc(sizeof(osa_msg_t));

    osa_msg_init(p, id, cmd, data, size);

    return p;
}


void        osa_msg_delete(osa_msg_t *msg)
{
    if (msg->data)
    {
        osa_msg_fini(msg);
    }

    osa_mem_free(msg);
}


void    osa_msg_init(osa_msg_t *msg, osa_uint32_t id, osa_char_t *cmd, void *data, osa_size_t size)
{
    osa_mem_zero(msg, sizeof(osa_msg_t));

    msg->header.id = id;

    strncpy(msg->header.cmd, cmd, MSG_CMD_LEN_MAX-1);
    msg->header.result = OSA_ERR_ERR;
    msg->header.data_size = size;

    osa_char_t *p = NULL;

    if (data)
    {
        p = (char *)osa_mem_alloc(size + 1);
        memcpy(p, data, size);

        p[size] = '\0';
    }

    msg->data = (void *)p;
}


void    osa_msg_fini(osa_msg_t *msg)
{
    if (msg->data)
    {
        osa_mem_free(msg->data);
    }
    msg->header.data_size = 0;
}


void    osa_msg_set_result(osa_msg_t *msg, osa_err_t result)
{
    msg->header.result = result;
}


osa_char_t  *osa_msg_pack(osa_msg_t *msg)
{
    osa_size_t sz = sizeof(osa_msgheader_t) + msg->header.data_size;

    osa_char_t *p = (char *)osa_mem_alloc(sz + 1);

    /** copy header */
    memcpy(p, &msg->header, sizeof(osa_msgheader_t));
    /** copy data */
    if (msg->header.data_size > 0 && msg->data)
    {
        memcpy(p+sizeof(osa_msgheader_t), msg->data, msg->header.data_size);
    }

    // 打包后最后一个字节为'\0'
    p[sz] = '\0';

    return p;
}


osa_msg_t   *osa_msg_unpack(osa_char_t *str)
{
    osa_msg_t *p = osa_msg_new();
    if (!p)
    {
        osa_log_error("Failed to new message!\n");

        return NULL;
    }

    /** copy header */
    memcpy(p, str, sizeof(osa_msgheader_t));

    /** copy data */
    osa_char_t *d = NULL;
    if (p->header.data_size > 0)
    {
        d = (char *)osa_mem_alloc(p->header.data_size + 1);
        memcpy(d, str+sizeof(osa_msgheader_t), p->header.data_size);
        d[p->header.data_size] = '\0';
    }

    p->data = (void *)d;

    return p;
}


void        osa_msg_dump(osa_msg_t *msg)
{
    if (!msg)
    {
        return;
    }

    printf("-----------------------------------------------\n");
    printf("id      : %d\n", msg->header.id);
    printf("cmd     : %s\n", msg->header.cmd);
    printf("result  : %d\n", msg->header.result);
    printf("datasz  : %d\n", msg->header.data_size);
    if (msg->data)
    {
        printf("data    : %s\n", (char *)msg->data);
    }
    printf("\n");
}


osa_err_t   osa_msg_send(osa_ioch_t *ioch, osa_msg_t *msg)
{
    if (ioch->iofd < 0)
    {
        osa_log_error("Please open I/O channel at first!\n");
        return OSA_ERR_ERR;
    }

    if (!ioch->write)
    {
        osa_log_error("I/O channel no write operation !\n");
        return OSA_ERR_ERR;
    }

    osa_char_t *send_data = osa_msg_pack(msg);
    osa_size_t send_size = OSA_MSG_SEND_SIZE(msg);
    osa_size_t sz = 0;

    sz = ioch->write(ioch, send_data, send_size);

    if (sz != send_size)
    {
        osa_log_warn("The real send size is %d\n", sz);
    }

    osa_mem_free(send_data);

    return OSA_ERR_OK;
}


osa_err_t   osa_msg_recv(osa_ioch_t *ioch, osa_msg_t *out_msg)
{
    if (ioch->iofd < 0)
    {
        osa_log_error("Please open I/O channel at first!\n");
        return OSA_ERR_ERR;
    }

    if (!ioch->read)
    {
        osa_log_error("I/O channel no read operation !\n");
        return OSA_ERR_ERR;
    }

    osa_char_t buf[2048] = {0};

    osa_size_t sz = ioch->read(ioch, buf, sizeof(buf));
    if (sz >= sizeof(buf))
    {
        osa_log_warn("Buffer is too small!\n");
    }

    osa_msg_t *recv_msg = osa_msg_unpack(buf);

    osa_msg_init(out_msg, recv_msg->header.id, recv_msg->header.cmd, recv_msg->data, recv_msg->header.data_size);

    out_msg->header.result = recv_msg->header.result;

    return OSA_ERR_OK;
}


osa_err_t osa_msg_send_recv(osa_ioch_t *ioch, osa_msg_t *sndmsg, osa_msg_t *out_rcvmsg, osa_uint32_t timeout_secs)
{
    if (!ioch->iofd)
    {
        osa_log_error("Please open I/O channel at first!\n");
        return OSA_ERR_ERR;
    }

    osa_msg_send(ioch, sndmsg);

    osa_int32_t ret;
    osa_fdset_t readfds;
    osa_uint32_t remain_time = timeout_secs;
    osa_err_t err;

    osa_timeval_t timeout;

    osa_timeval_t start_time, end_time;

    while (remain_time > 0)
    {
        osa_time_gettimeofday(&start_time);

        FD_ZERO(&readfds);
        FD_SET(ioch->iofd, &readfds);

        timeout.tv_sec = remain_time;
        timeout.tv_usec = 0;

        ret = osa_select(ioch->iofd+1, &readfds, NULL, NULL, &timeout);

        if (ret == OSA_SELECT_ERROR)
        {
            osa_log_error("Select error when receive message!\n");
            err = OSA_ERR_ERR;
            break;
        }
        else if (ret == OSA_SELECT_TIMEOUT)
        {
            return OSA_ERR_ERR;
            remain_time = 0;
            continue;
        }
        else
        {
            if (FD_ISSET(ioch->iofd, &readfds))
            {
                osa_msg_recv(ioch, out_rcvmsg);
                if (sndmsg->header.id == out_rcvmsg->header.id)
                {
                    err = OSA_ERR_OK;
                    break;
                }
            }
        }

        osa_time_gettimeofday(&end_time);

        // ignore microsecond of time
        remain_time -= 1 * (end_time.tv_sec - start_time.tv_sec);
    }

    return err;
}
