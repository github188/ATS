/*
 * report.c
 *
 * Copyright (C) TuoAn
 *
 */

#include "osa.h"
#include "module.h"
#include "ats.h"
#include "conf_xml.h"
#include "log.h"
#include "report.h"



ATS_Report  *g_reportFile;


static osa_err_t   reportConfRead(ATS_Conf *cf, void *out_data);
static osa_err_t   reportConfWrite(ATS_Conf *cf, void *data);
static osa_err_t   reportModuleEntry(ATS_Conf *cf, int argc, char **argv);
static void        reportModuleExit(ATS_Conf *cf);


static ATS_Module  reportModule =
{
    .name   = "report",
    .state  = ATS_MODULE_ON,
    .cfops     =
    {
        .open   = NULL,
        .close  = NULL,
        .read   = reportConfRead,
        .write  = reportConfWrite,
        .ctrl   = NULL,
    },
    .entry  = reportModuleEntry,
    .exit   = reportModuleExit,
};



osa_err_t   ATS_ReportModuleInit(ATS_Conf *cf)
{
    reportModule.cf = cf;

    ATS_ModuleRegister(&reportModule);

    return OSA_ERR_OK;
}

void        ATS_ReportModuleExit()
{
    ATS_ModuleUnregister(&reportModule);
}


osa_err_t   reportConfRead(ATS_Conf *cf, void *out_data)
{
    XML_ReportModuleRead(cf, out_data);
    return OSA_ERR_OK;
}

osa_err_t   reportConfWrite(ATS_Conf *cf, void *data)
{
    return OSA_ERR_OK;
}

osa_err_t   reportModuleEntry(ATS_Conf *cf, int argc, char **argv)
{
    CONF_Test   reportConf;

    ATS_ConfSetModuleConf(cf, &reportModule);
    ATS_ConfRead(cf, &reportConf);

    // 如果模块为关闭状态，则不处理
    if (reportConf.state == ATS_MODULE_OFF)
    {
        return OSA_ERR_ERR;
    }
    else
    {
        return OSA_ERR_OK;
    }
}

void    reportModuleExit(ATS_Conf *cf)
{

}
