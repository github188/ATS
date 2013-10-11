/**
 *  sdk_module.c
 *
 */


#include "osa.h"
#include "module.h"
#include "conf.h"
#include "log.h"
#include "module/sdk.h"


static ats_module_t     sdk_module;
static ats_mops_t       sdk_mops;


osa_err_t osa_sdk_mod_init()
{
    sdk_mops.begin = NULL;
    sdk_mops.end = NULL;
    
    return ats_module_register(&sdk_module, "sdk", &sdk_mops);
}

void osa_sdk_mod_exit()
{
    ats_module_unregister("sdk");
}