/**
 *  socket_report.c
 *
 */


/**
 *  UDP/ SOCK_DGRAM数据传输
 *
 */

#include "osa.h"
#include "report.h"
#include "cJSON.h"
#include "log.h"


osa_socket_t *reportSock = NULL;

osa_err_t   socketReportOpen(ATS_Report *self, void *priv);
osa_err_t   socketReportClose(ATS_Report *self);
osa_size_t  socketReportWrite(ATS_Report *self, const osa_char_t *buf, osa_size_t size);
osa_size_t  socketReportRead(ATS_Report *self, osa_char_t *outBuf, osa_size_t size);
osa_err_t   socketReportCtrl(ATS_Report *self, osa_uint32_t cmd, void *arg);


void        ATS_ReportSysInit(ATS_Report *report)
{
    report->open = socketReportOpen;
    report->close = socketReportClose;
    report->write = socketReportWrite;
    report->read = socketReportRead;
    report->ctrl = socketReportCtrl;
}


osa_err_t   socketReportOpen(ATS_Report *self, void *priv)
{
    // priv : osa_sockaddr_t *
    self->priv = priv;

    if (reportSock)
    {
        socketReportClose(self);
    }


    reportSock = osa_udpsock_open();

    return OSA_ERR_OK;
}


osa_err_t   socketReportClose(ATS_Report *self)
{
    if (reportSock)
    {
        osa_udpsock_close(reportSock);
    }

    reportSock = NULL;

    return OSA_ERR_OK;
}

osa_size_t  socketReportWrite(ATS_Report *self, const osa_char_t *buf, osa_size_t size)
{
    osa_size_t sz = 0;

    if (!reportSock)
    {
        ATS_LogError("Please open socket first!\n");
        return 0;
    }

    osa_sockaddr_t  reportAddr, *paddr;
    paddr = self->priv;

    // port : 3000
    osa_sockaddr_set(&reportAddr, inet_ntoa(paddr->in_addr.sin_addr), 3000);

    sz = osa_udpsock_write_dgram(reportSock, buf, size, &reportAddr);

    return sz;
}


osa_size_t  socketReportRead(ATS_Report *self, osa_char_t *outBuf, osa_size_t size)
{
    if (!reportSock)
    {
        ATS_LogError("Please open socket first!\n");
        return 0;
    }

    return 0;
}


osa_err_t   socketReportCtrl(ATS_Report *self, osa_uint32_t cmd, void *arg)
{
    return OSA_ERR_OK;
}

