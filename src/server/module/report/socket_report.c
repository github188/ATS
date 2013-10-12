/**
 *  socket_report.c
 *
 */


#include "osa.h"
#include "cJSON.h"
#include "log.h"
#include "module/report.h"


static osa_socket_t  *report_sock;
static osa_sockaddr_t report_addr;


ats_report_t *ats_report_open(void *user_data)
{
    report_sock = osa_udpsock_open();
    if (!report_sock)
    {
        ats_log_error("Failed to open report socket!\n");
        return NULL;
    }
    
    ats_report_t *rpt = (ats_report_t *)osa_mem_alloc(sizeof(ats_report_t));
    
    rpt->fd = -1;
    rpt->user_data = user_data;
    
    osa_sockaddr_t  *paddr = (osa_sockaddr_t *)user_data;

    osa_sockaddr_set(&report_addr, inet_ntoa(paddr->in_addr.sin_addr), 3000);
    
    return rpt;
}

void ats_report_close(ats_report_t *rpt)
{
    if (rpt->fd > 0)
    {
        osa_udpsock_close(report_sock);
    }
    report_sock = NULL;
    osa_mem_free(rpt);
}

osa_size_t ats_report_write(ats_report_t *rpt, const osa_char_t *buf, osa_size_t size)
{
    if (!report_sock)
    {
        return 0;
    }
    
    return osa_udpsock_write_dgram(report_sock, buf, size, &report_addr);
}

osa_size_t ats_report_read(ats_report_t *rpt, osa_char_t *out_buf, osa_size_t size)
{
    if (!report_sock)
    {
        return 0;
    }
    
    return osa_udpsock_read_dgram(report_sock, out_buf, size);
}

osa_err_t    ats_report_ctrl(ats_report_t *rpt, osa_uint32_t cmd, void *param)
{
    return OSA_ERR_ERR;
}
