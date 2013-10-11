/**
 *  socket_report.c
 *
 */


/**
 *  UDP/ SOCK_DGRAM数据传输
 *
 */

#include "osa.h"
#include "cJSON.h"
#include "log.h"
#include "module/report.h"


osa_socket_t *reportSock = NULL;

osa_err_t   sock_report_open(ats_report_t *self, void *user_data);
osa_err_t   sock_report_close(ats_report_t *self);
osa_size_t  sock_report_write(ats_report_t *self, const osa_char_t *buf, osa_size_t size);
osa_size_t  sock_report_read(ats_report_t *self, osa_char_t *outBuf, osa_size_t size);
osa_err_t   sock_report_ctrl(ats_report_t *self, osa_uint32_t cmd, void *arg);


void ATS_ReportSysInit(ats_report_t *report)
{
    report->open = sock_report_open;
    report->close = sock_report_close;
    report->write = sock_report_write;
    report->read = sock_report_read;
    report->ctrl = sock_report_ctrl;
}


osa_err_t   sock_report_open(ats_report_t *self, void *user_data)
{
    // priv : osa_sockaddr_t *
    self->user_data = user_data;

    if (reportSock)
    {
        sock_report_close(self);
    }


    reportSock = osa_udpsock_open();

    return OSA_ERR_OK;
}


osa_err_t   sock_report_close(ats_report_t *self)
{
    if (reportSock)
    {
        osa_udpsock_close(reportSock);
    }

    reportSock = NULL;

    return OSA_ERR_OK;
}

osa_size_t  sock_report_write(ats_report_t *self, const osa_char_t *buf, osa_size_t size)
{
    osa_size_t sz = 0;

    if (!reportSock)
    {
        ats_log_error("Please open socket first!\n");
        return 0;
    }

    osa_sockaddr_t  reportAddr, *paddr;
    paddr = self->user_data;

    // port : 3000
    osa_sockaddr_set(&reportAddr, inet_ntoa(paddr->in_addr.sin_addr), 3000);

    sz = osa_udpsock_write_dgram(reportSock, buf, size, &reportAddr);

    return sz;
}


osa_size_t  sock_report_read(ats_report_t *self, osa_char_t *outBuf, osa_size_t size)
{
    if (!reportSock)
    {
        ats_log_error("Please open socket first!\n");
        return 0;
    }

    return 0;
}


osa_err_t   sock_report_ctrl(ats_report_t *self, osa_uint32_t cmd, void *arg)
{
    return OSA_ERR_OK;
}

