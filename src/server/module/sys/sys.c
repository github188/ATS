/**
 *  sys.c
 *
 */



#include <time.h>

#include "osa.h"
#include "log.h"
#include "conf_xml.h"
#include "sys_business.h"
#include "device.h"
#include "dev_bus.h"


#define     CLIENT_MAX      100

#define     SYS_PORT    2000


static osa_tcpserver_t  *sysServer;
static osa_socket_t     *clientSock[CLIENT_MAX] = {NULL};
static osa_fdset_t      readfds;
static osa_ioch_t       sysIOCH;



static void        _doSysBusiness(osa_socket_t *sock, osa_msg_t *msg);
static osa_err_t   _sysIOCHOpen(osa_ioch_t *self, void *param);
static osa_err_t   _sysIOCHClose(osa_ioch_t *self);
static osa_size_t  _sysIOCHWrite(osa_ioch_t *self, osa_char_t *data, osa_size_t size);
static osa_size_t  _sysIOCHRead(osa_ioch_t *self, osa_char_t *out_data, osa_size_t size);


void    ATS_SysInit()
{
    ats_log_info("Initialize system !\n");

    osa_err_t   err;

    sysServer = osa_tcpserver_open();
    if (!sysServer)
    {
        ats_log_error("Failed to open agent socket!\n");
        return;
    }

    osa_sockaddr_t  serverAddr;

    osa_sockaddr_set(&serverAddr, INADDR_ANY, SYS_PORT);

    err = osa_tcpserver_listen(sysServer, &serverAddr);
    if (err != OSA_ERR_OK)
    {
        ats_log_error("Failed to listen socket!\n");
    }

    sysIOCH.open    = _sysIOCHOpen;
    sysIOCH.close   = _sysIOCHClose;
    sysIOCH.read    = _sysIOCHRead;
    sysIOCH.write   = _sysIOCHWrite;
}


void    ATS_SysExec()
{
    ats_log_info("Start system message loop!\n");

    osa_int32_t     ret = 0;
    osa_char_t      buf[2048];
    osa_sfd_t       maxfd = sysServer->fd;
    osa_uint32_t    idx = 0;
    struct timeval  timeout;
    osa_int32_t     val = 0;

    while (1)
    {
        val = osa_tcpserver_accept(sysServer, 4);

        // timeout
        if (val == 0)
        {
            continue;
        }
        else if (val == OSA_SOCK_HAS_ERROR)
        {
            continue;
        }
        else if (val == OSA_SOCK_HAS_CONNECT)
        {
            for (idx=0; idx<CLIENT_MAX; idx++)
            {
                if (!clientSock[idx])
                {
                    clientSock[idx] = osa_tcpserver_get_client(sysServer);
                    ats_log_info("New client connected : %d\n", clientSock[idx]->fd);
                    break;
                }
            }
        }
        else if (val == OSA_SOCK_HAS_DATA)
        {
            ats_log_info("Received data from client!\n");

            osa_size_t recvSize = 0;
            for (idx=0; idx<CLIENT_MAX; idx++)
            {
                if (clientSock[idx] && osa_tcpserver_client_ready(sysServer, clientSock[idx]) == OSA_TRUE)
                {
                    memset(buf, 0, sizeof(buf));

                    recvSize = osa_tcpclient_read(clientSock[idx], buf, sizeof(buf)-1);

                    // socket可读但是没有接收到数据，认为是客户端断线了,关闭客户端连接
                    if (recvSize == 0 || recvSize == -1)
                    {
                        ats_log_warn("Bye, client lost : %d\n", clientSock[idx]->fd);

                        osa_tcpserver_close_client(sysServer, clientSock[idx]);
                        clientSock[idx] = NULL;

                        continue;
                    }

                    if (recvSize > sizeof(buf)-1)
                    {
                        ats_log_error("buffer is too small !\n");
                        buf[sizeof(buf)-1] = '\0';
                    }

                    osa_msg_t *msg = osa_msg_unpack(buf);

                    if (!strcmp(msg->header.cmd, "ExitSystem"))
                    {
                        ats_log_info("Client exit : %d\n", clientSock[idx]->fd);

                        osa_tcpserver_close_client(sysServer, clientSock[idx]);

                        clientSock[idx] = NULL;
                    }
                    else
                    {
                        _doSysBusiness(clientSock[idx], msg);
                    }

                    osa_msg_delete(msg);
                }
            }
        }
    }
}


static osa_err_t   _sysIOCHOpen(osa_ioch_t *self, void *param)
{
    osa_socket_t *client = (osa_socket_t *)param;

    self->iofd = client->fd;
    self->priv = client;

    return OSA_ERR_OK;
}


static osa_err_t   _sysIOCHClose(osa_ioch_t *self)
{
    self->iofd = -1;
    self->priv = NULL;

    return OSA_ERR_OK;
}


static osa_size_t  _sysIOCHWrite(osa_ioch_t *self, osa_char_t *data, osa_size_t size)
{
    if (!self->priv || self->iofd < 0)
    {
        ats_log_error("Please open I/O channel first!\n");
        return 0;
    }

    return osa_tcpclient_write((osa_socket_t *)self->priv, data, size);
}


static osa_size_t  _sysIOCHRead(osa_ioch_t *self, osa_char_t *out_data, osa_size_t size)
{
    if (!self->priv || self->iofd < 0)
    {
        ats_log_error("Please open I/O channel first!\n");
        return 0;
    }

    return osa_tcpclient_read((osa_socket_t *)self->priv, out_data, size);
}


static void _doSysBusiness(osa_socket_t *sock, osa_msg_t *msg)
{
    // 打开消息通道
    sysIOCH.open(&sysIOCH, sock);

    osa_msg_dump(msg);

    osa_char_t *cmd = msg->header.cmd;

    if (!strcmp(cmd, "LoginSystem"))
    {
        sysLogin(&sysIOCH, msg);
    }
    else if (!strcmp(cmd, "GetDevices"))
    {
        sysGetDevs(&sysIOCH, msg);
    }
    else if (!strcmp(cmd, "TestDevice"))
    {
        sysTestDevice(&sysIOCH, msg);
    }
    else if (!strcmp(cmd, "LoginDevice"))
    {
        sysLoginDevice(&sysIOCH, msg);
    }


    // 关闭消息通道
    sysIOCH.close(&sysIOCH);

}

