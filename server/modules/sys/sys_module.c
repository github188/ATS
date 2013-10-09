/**
 *  sys_module.c
 *
 */

#include "osa.h"
#include "module.h"
#include "ats.h"
#include "conf_xml.h"
#include "log.h"
#include "sys.h"

static osa_err_t   sysConfRead(ATS_Conf *cf, void *out_data);
static osa_err_t   sysConfWrite(ATS_Conf *cf, void *data);
static osa_err_t   sysModuleEntry(ATS_Conf *cf, int argc, char **argv);
static void        sysModuleExit(ATS_Conf *cf);


static ATS_Module  sysModule =
{
    .name   = "sys",
    .state  = ATS_MODULE_ON,
    .cfops     =
    {
        .open   = NULL,
        .close  = NULL,
        .read   = sysConfRead,
        .write  = sysConfWrite,
        .ctrl   = NULL,
    },
    .entry  = sysModuleEntry,
    .exit   = sysModuleExit,
};



osa_err_t   ATS_SysModuleInit(ATS_Conf *cf)
{
    sysModule.cf = cf;
    ATS_ModuleRegister(&sysModule);

    return OSA_ERR_OK;
}

void    ATS_SysModuleExit()
{
    ATS_ModuleUnregister(&sysModule);
}


static osa_err_t   sysConfRead(ATS_Conf *cf, void *out_data)
{
    return OSA_ERR_OK;
}

static osa_err_t   sysConfWrite(ATS_Conf *cf, void *data)
{
    return OSA_ERR_OK;
}

static osa_err_t   sysModuleEntry(ATS_Conf *cf, int argc, char **argv)
{
    ATS_SysInit();

    return OSA_ERR_OK;
}

static void    sysModuleExit(ATS_Conf *cf)
{
}
