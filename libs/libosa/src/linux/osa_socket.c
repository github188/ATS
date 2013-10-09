/**
 *  osa_socket.c
 *
 */

#include "osa_types.h"
#include "osa_socket.h"
#include "osa_error.h"
#include "osa_log.h"
#include "osa_mem.h"
#include "osa_select.h"
#include "osa_macro.h"
#include "osa_string.h"

#include <sys/socket.h>
#include <netinet/in.h>



void    osa_sockaddr_set(osa_sockaddr_t *addr, const osa_char_t *ip, osa_uint32_t port)
{
    memset(addr, 0, sizeof(osa_sockaddr_t));

    addr->in_addr.sin_family = AF_INET;
    if (ip == INADDR_ANY)
    {
        addr->in_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    }
    else
    {
        addr->in_addr.sin_addr.s_addr = inet_addr(ip);
    }
    addr->in_addr.sin_port = htons(port);
}

osa_socket_t    *osa_tcpclient_open()
{
    osa_socket_t *sock = osa_mem_alloc(sizeof(osa_socket_t));

    if ((sock->fd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        osa_log_error("Failed to build socket!\n");
        osa_mem_free(sock);
        return NULL;
    }

    char yes = 1;
    if (setsockopt(sock->fd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int)) < 0)
    {
        osa_log_error("Failed to set socket!\n");
    }

    osa_list_init(&sock->list);

    return sock;
}


osa_err_t       osa_tcpclient_close(osa_socket_t *sock)
{
    osa_list_remove(&sock->list);

    if (sock && sock->fd > 0)
    {
        close(sock->fd);
    }

    osa_mem_free(sock);

    return OSA_ERR_OK;
}

osa_err_t       osa_tcpclient_connect(osa_socket_t *sock,  osa_sockaddr_t *addr)
{

    if (sock->fd > 0 && connect(sock->fd, (struct sockaddr *)&addr->in_addr, sizeof(struct sockaddr_in)) < 0)
    {
        osa_log_error("Failed to connect to server!\n");

        return OSA_ERR_ERR;
    }

    return OSA_ERR_OK;
}

osa_size_t      osa_tcpclient_write(osa_socket_t *sock, osa_char_t *buf, osa_size_t size)
{
    osa_size_t sendsz = 0;

    if (sock->fd > 0 && (sendsz = send(sock->fd, buf, size, 0)) != size)
    {
        osa_log_warn("data should send %d bytes, but the real size is %d bytes!\n", size, sendsz);
    }

    osa_log_info("send %d bytes data!\n", sendsz);

    return sendsz;
}


osa_size_t      osa_tcpclient_read(osa_socket_t *sock, osa_char_t *out_buf, osa_size_t size)
{
    osa_size_t recvsz = 0;

    if (sock->fd > 0 && (recvsz = recv(sock->fd, out_buf, size, 0)) != size)
    {
        osa_log_warn("data should receive %d bytes, but the real size is %d bytes!\n", size, recvsz);
    }

    osa_log_info("received %d bytes data!\n", recvsz);

    return recvsz;
}

osa_tcpserver_t *osa_tcpserver_open()
{
    osa_tcpserver_t *sock = osa_mem_alloc(sizeof(osa_tcpserver_t));

    if ((sock->fd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        osa_log_error("Failed to open socket!\n");
        osa_mem_free(sock);
        return NULL;
    }

    osa_int8_t yes = 1;
    if (setsockopt(sock->fd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int)) < 0)
    {
        osa_log_error("Failed to set socket!\n");
    }

    osa_list_init(&sock->clientListHead);

    sock->maxfd = sock->fd;

    FD_ZERO(&sock->readfds);

    return sock;
}

osa_err_t       osa_tcpserver_close(osa_tcpserver_t *sock)
{
    osa_list_t  *l = NULL;
    osa_socket_t *node = NULL;

    // close all of client connected to this server
    for (l=sock->clientListHead.next; l!=&sock->clientListHead; l=l->next)
    {
        node = osa_list_entry(l, osa_socket_t, list);
        osa_tcpserver_close_client(sock, node);
    }

    if (sock->fd > 0)
    {
        close(sock->fd);
    }

    osa_mem_free(sock);

    return OSA_ERR_OK;
}

osa_err_t       osa_tcpserver_listen(osa_tcpserver_t *sock, osa_sockaddr_t *addr)
{
    if (sock->fd < 0)
    {
        return OSA_ERR_ERR;
    }

    if ((bind(sock->fd, (struct sockaddr *)&addr->in_addr, sizeof(struct sockaddr_in))) < 0)
    {
        osa_log_error("Failed to bind socket!\n");
        return OSA_ERR_ERR;
    }

    if (listen(sock->fd, OSA_SOCK_BACKLOG) != 0)
    {
        osa_log_error("Failed to listen socket!\n");
        return OSA_ERR_ERR;
    }

    return OSA_ERR_OK;
}

osa_err_t       osa_tcpserver_close_client(osa_tcpserver_t *sock, osa_socket_t *client)
{
    FD_CLR(client->fd, &sock->readfds);

    return osa_tcpclient_close(client);
}

osa_int32_t     osa_tcpserver_accept(osa_tcpserver_t *sock, osa_uint32_t timeout_secs)
{
    osa_int32_t ret = 0;
    osa_list_t *l = NULL;
    osa_socket_t *node = NULL;

    struct timeval  timeout;

    timeout.tv_sec = timeout_secs;
    timeout.tv_usec = 0;

    FD_ZERO(&sock->readfds);
    FD_ZERO(&sock->expfds);

    // add server socket to the monitor list
    FD_SET(sock->fd, &sock->readfds);
    FD_SET(sock->fd, &sock->expfds);

    // add all client into the monitor list
    for (l=sock->clientListHead.next; l!=&sock->clientListHead; l=l->next)
    {
        node = osa_list_entry(l, osa_socket_t, list);
        if (node->fd > 0)
        {
            FD_SET(node->fd, &sock->readfds);
            FD_SET(node->fd, &sock->expfds);
        }
    }

    // select
    ret = osa_select(sock->maxfd +1, &sock->readfds, NULL, NULL, &timeout);

    if (ret < 0)
    {
        osa_log_error("socket select error!\n");

        for (l=sock->clientListHead.next; l!=&sock->clientListHead; l=l->next)
        {
            node = osa_list_entry(l, osa_socket_t, list);
            if (FD_ISSET(node->fd, &sock->expfds))
            {
                osa_tcpserver_close_client(sock, node);
            }
        }

        return OSA_SOCK_HAS_ERROR;
    }
    else if (ret == 0)
    {
        return 0;
    }
    else
    {
        // new client connected
        if (FD_ISSET(sock->fd, &sock->readfds))
        {
            osa_socket_t *client = (osa_socket_t *)osa_mem_alloc(sizeof(osa_socket_t));

            osa_uint32_t  addrsz = sizeof(struct sockaddr_in);

            client->fd = accept(sock->fd, (struct sockaddr *)&client->addr.in_addr, &addrsz);
            if (client->fd <= 0)
            {
                osa_log_error("Failed to accept socket!\n");
            }

            osa_list_init(&client->list);

            // add client to the end of list
            osa_list_insert_before(&sock->clientListHead, &client->list);

            sock->maxfd = OSA_MAX(sock->maxfd, client->fd);

            // attention: if there is a new connection or data at same time, we just deal with the new connection
            return OSA_SOCK_HAS_CONNECT;
        }

#if 0
        for (l=sock->clientListHead.next; l!=&sock->clientListHead; l=l->next)
        {
            node = osa_list_entry(l, osa_socket_t, list);

            if (FD_ISSET(node->fd, &sock->readfds))
            {
                return OSA_SOCK_HAS_DATA;
            }
        }
#endif

        return OSA_SOCK_HAS_DATA;
    }
}

osa_socket_t    *osa_tcpserver_get_client(osa_tcpserver_t *sock)
{
    osa_socket_t *lastClient = NULL;

    // get the latest client connected to server
    osa_list_t *lastClientList = sock->clientListHead.prev;
    lastClient = osa_list_entry(lastClientList, osa_socket_t, list);

    return lastClient;
}


osa_bool_t      osa_tcpserver_client_ready(osa_tcpserver_t *sock, osa_socket_t *client)
{
    if (FD_ISSET(client->fd, &sock->readfds))
    {
        return OSA_TRUE;
    }
    return OSA_FALSE;
}


osa_socket_t    *osa_udpsock_open()
{
    osa_socket_t *sock = osa_mem_alloc(sizeof(osa_socket_t));

    if ((sock->fd = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
    {
        osa_log_error("Failed to build socket!\n");
        osa_mem_free(sock);
        return NULL;
    }

    char yes = 1;
    if (setsockopt(sock->fd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int)) < 0)
    {
        osa_log_error("Failed to set socket!\n");
    }

    osa_list_init(&sock->list);

    return sock;

}


osa_err_t       osa_udpsock_close(osa_socket_t *sock)
{
    osa_list_remove(&sock->list);

    if (sock && sock->fd > 0)
    {
        close(sock->fd);
    }

    osa_mem_free(sock);

    return OSA_ERR_OK;

}


osa_err_t       osa_udpsock_bind(osa_socket_t *sock, osa_sockaddr_t *addr)
{
    if ((bind(sock->fd, (struct sockaddr *)&addr->in_addr, sizeof(struct sockaddr_in))) < 0)
    {
        osa_log_error("Failed to bind socket!\n");
        return OSA_ERR_ERR;
    }

    return OSA_ERR_OK;
}


osa_size_t      osa_udpsock_write_dgram(osa_socket_t *sock, void *data, osa_size_t size, osa_sockaddr_t *addr)
{
    osa_size_t sz = sendto(sock->fd, data, size, 0, (struct sockaddr *)&addr->in_addr, sizeof(struct sockaddr_in));
    if (sz != size)
    {
        osa_log_warn("The actuial bytes to send is %d\n", sz);
    }

    return sz;
}


osa_int32_t osa_udpsock_wait_dgram(osa_socket_t *sock, osa_uint32_t timeout_secs)
{
    osa_fdset_t readfds;
    osa_int32_t ret  = 0;

    struct timeval  timeout;

    timeout.tv_sec = timeout_secs;
    timeout.tv_usec = 0;

    FD_ZERO(&readfds);

    // add server socket to the monitor list
    FD_SET(sock->fd, &readfds);

    // select
    ret = osa_select(sock->fd+1, &readfds, NULL, NULL, &timeout);

    if (ret < 0)
    {
        osa_log_error("socket select error!\n");

        return OSA_SOCK_HAS_ERROR;
    }
    else if (ret == 0)
    {
        return 0;
    }
    else
    {
        if (FD_ISSET(sock->fd, &readfds))
        {
            return OSA_SOCK_HAS_DATA;
        }

        return OSA_SOCK_HAS_ERROR;
    }
}


osa_size_t  osa_udpsock_read_dgram(osa_socket_t *sock, void *out_data, osa_size_t size)
{
    osa_sockaddr_t  client;
    osa_size_t  addrsz = sizeof(struct sockaddr);

    osa_size_t sz = recvfrom(sock->fd, out_data, size, 0, (struct sockaddr *)&client.in_addr, &addrsz);
    if (sz != size)
    {
        osa_log_warn("The actual size of data is %d bytes!\n", sz);
    }

    return sz;
}

