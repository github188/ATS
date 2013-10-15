/**
 *  osa_socket.h
 *
 */


#ifndef __OSA_SOCKET_H__
#define __OSA_SOCKET_H__


#include "osa_types.h"
#include "osa_error.h"
#include "osa_list.h"
#include "osa_select.h"


#ifdef __OSA_OS_LINUX__
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
typedef osa_int32_t    osa_sfd_t;
#endif

#ifdef __OSA_OS_WIN32__
typedef SOCKET          osa_sfd_t;
#endif


#ifdef __cplusplus
extern "C"
{
#endif


typedef struct _OSA_SOCKADDR
{
    union
    {
        struct sockaddr     addr;
        struct sockaddr_in  in_addr;
    };
} osa_sockaddr_t;


OSA_API void    osa_sockaddr_set(osa_sockaddr_t *addr, 
                                const osa_char_t *ip, 
                                osa_uint32_t port);


typedef struct _OSA_SOCKET
{
    osa_sfd_t       fd;
    osa_sockaddr_t  addr;
    osa_list_t      list;
} osa_socket_t;


typedef struct _OSA_TCP_SERVER
{
    osa_sfd_t       fd;
    osa_list_t      clientListHead;
    osa_fdset_t     readfds;
    osa_fdset_t     expfds;
    osa_sfd_t       maxfd;
} osa_tcpserver_t;


#define OSA_SOCK_BACKLOG    10


#define    OSA_SOCK_HAS_ERROR       OSA_SELECT_ERROR
#define    OSA_SOCK_HAS_CONNECT     1
#define    OSA_SOCK_HAS_DATA        2

// TCP socket
OSA_API osa_socket_t *osa_tcpclient_open();
OSA_API osa_err_t    osa_tcpclient_close(osa_socket_t *sock);
OSA_API osa_err_t    osa_tcpclient_connect(osa_socket_t *sock, 
                                            osa_sockaddr_t *addr);
OSA_API osa_size_t   osa_tcpclient_write(osa_socket_t *sock, 
                                        osa_char_t *buf, 
                                        osa_size_t size);
OSA_API osa_size_t   osa_tcpclient_read(osa_socket_t *sock, 
                                        osa_char_t *out_buf, 
                                        osa_size_t size);


OSA_API osa_tcpserver_t *osa_tcpserver_open();
OSA_API osa_err_t   osa_tcpserver_close(osa_tcpserver_t *sock);
OSA_API osa_err_t   osa_tcpserver_close_client(osa_tcpserver_t *sock, 
                                        osa_socket_t *client);
OSA_API osa_err_t   osa_tcpserver_listen(osa_tcpserver_t *sock, 
                                        osa_sockaddr_t *addr);
OSA_API osa_int32_t osa_tcpserver_accept(osa_tcpserver_t *sock, 
                                        osa_uint32_t timeout_secs);
OSA_API osa_socket_t *osa_tcpserver_get_client(osa_tcpserver_t *sock);
OSA_API osa_bool_t   osa_tcpserver_client_ready(osa_tcpserver_t *sock, 
                                        osa_socket_t *client);


// UDP socket
OSA_API osa_socket_t *osa_udpsock_open();
OSA_API osa_err_t    osa_udpsock_close(osa_socket_t *sock);
OSA_API osa_err_t    osa_udpsock_bind(osa_socket_t *sock, 
                                    osa_sockaddr_t *addr);
OSA_API osa_size_t   osa_udpsock_write_dgram(osa_socket_t *sock, 
                                    const void *data, osa_size_t size, 
                                    osa_sockaddr_t *addr);
OSA_API osa_int32_t  osa_udpsock_wait_dgram(osa_socket_t *sock, 
                                    osa_uint32_t timeout_secs);
OSA_API osa_size_t   osa_udpsock_read_dgram(osa_socket_t *sock, 
                                    void *out_data, osa_size_t size);


#ifdef __cplusplus
}
#endif

#endif
