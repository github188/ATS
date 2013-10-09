/**
 *  sdk_module.c
 *
 */


#include "ats.h"
#include "osa.h"
#include "module.h"
#include "conf.h"
#include "log.h"
#include "sdk.h"



static osa_err_t    sdkModuleEntry(ATS_Conf *cf, int argc, char **argv);
static void         sdkModuleExit(ATS_Conf *cf);


static ATS_Module  sdkModule =
{
    .name   = "sdk",
    .state  = ATS_MODULE_ON,
    .cfops     =
    {
        .open   = NULL,
        .close  = NULL,
        .read   = NULL,
        .write  = NULL,
        .ctrl   = NULL,
    },
    .entry  = sdkModuleEntry,
    .exit   = sdkModuleExit,
};



osa_err_t   ATS_SdkModuleInit(ATS_Conf *cf)
{
    sdkModule.cf = cf;

    ATS_ModuleRegister(&sdkModule);

    return OSA_ERR_OK;
}

void        ATS_SdkModuleExit()
{
    ATS_ModuleUnregister(&sdkModule);
}


static osa_err_t   sdkModuleEntry(ATS_Conf *cf, int argc, char **argv)
{
    return OSA_ERR_OK;
}


static void        sdkModuleExit(ATS_Conf *cf)
{
}
