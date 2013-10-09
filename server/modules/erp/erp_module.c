/*
 * erp.c
 *
 * Copyright (C) TuoAn
 *
 */

#include "osa.h"
#include "module.h"
#include "ats.h"
#include "conf_xml.h"
#include "log.h"


static osa_err_t   erpConfRead(ATS_Conf *cf, void *out_data);
static osa_err_t   erpConfWrite(ATS_Conf *cf, void *data);
static osa_err_t   erpModuleEntry(ATS_Conf *cf, int argc, char **argv);
static void        erpModuleExit(ATS_Conf *cf);


static ATS_Module  erpModule =
{
    .name   = "erp",
    .state  = ATS_MODULE_ON,
    .cfops     =
    {
        .open   = NULL,
        .close  = NULL,
        .read   = erpConfRead,
        .write  = erpConfWrite,
        .ctrl   = NULL,
    },
    .entry  = erpModuleEntry,
    .exit   = erpModuleExit,
};



osa_err_t   ATS_ErpModuleInit(ATS_Conf *cf)
{
    erpModule.cf = cf;
    ATS_ModuleRegister(&erpModule);

    return OSA_ERR_OK;
}

void    ATS_ErpModuleExit()
{
    ATS_ModuleUnregister(&erpModule);
}




osa_err_t   erpConfRead(ATS_Conf *cf, void *out_data)
{
    //XML_ErpModuleRead(cf, out_data);
    return OSA_ERR_OK;
}

osa_err_t   erpConfWrite(ATS_Conf *cf, void *data)
{
    return OSA_ERR_OK;
}

osa_err_t   erpModuleEntry(ATS_Conf *cf, int argc, char **argv)
{
    CONF_Erp   erpConf;

    ATS_ConfSetModuleConf(cf, &erpModule);
    ATS_ConfRead(cf, &erpConf);

    // 如果模块为关闭状态，则不处理
    if (erpConf.state == ATS_MODULE_OFF)
    {
        return OSA_ERR_OK;
    }
    else
    {
        return OSA_ERR_OK;
    }
}

void    erpModuleExit(ATS_Conf *cf)
{

}
