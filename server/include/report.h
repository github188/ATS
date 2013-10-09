/*
 * cat_report.h
 *
 * Copyright (C) TuoAn
 *
 */

#ifndef ATS_REPORT_H_
#define ATS_REPORT_H_

#include "ats.h"
#include "osa.h"
#include "conf.h"

// report interface
struct _ATS_REPORT_ITR
{
    // 文件：可以为socket, 本地文件等
    osa_uint32_t fd;
    void         *priv;

    osa_err_t   (*open)(ATS_Report *self, void *priv);
    osa_err_t   (*close)(ATS_Report *self);
    osa_size_t  (*write)(ATS_Report *self, const osa_char_t *buf, osa_size_t size);
    osa_size_t  (*read)(ATS_Report *self, osa_char_t *outBuf, osa_size_t size);
    osa_err_t   (*ctrl)(ATS_Report *self, osa_uint32_t cmd, void *arg);
};


osa_err_t   ATS_ReportModuleInit(ATS_Conf *cf);
void        ATS_ReportModuleExit();

void        ATS_ReportSysInit(ATS_Report *report);


// 全局变量
extern ATS_Report   *g_reportFile;

#endif /* ATS_REPORT_H_ */
