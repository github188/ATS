/**
 *  sdk.c
 *
 */
 
#include "osa.h"
#include "bus.h"
#include "sdk.h"


static osa_dll_t   sdk_dll;

ats_sdk_t   *ats_sdk_find(ats_bus_t *sdk_bus, const osa_char_t *sdk_name)
{
}

osa_err_t ats_sdk_register(ats_bus_t *sdk_bus, ats_sdk_t *sdk)
{
    ats_sdk_t *p = NULL;
    
    
    return OSA_ERR_OK;
}

osa_err_t ats_sdk_unregisetr(ats_bus_t *sdk_bus, const osa_char_t *sdk_name)
{
    
}

ats_sdk_t   *ats_sdk_plugin_load(const osa_char_t *plugin_file)
{
    ats_sdk_t *sdk = NULL;
    
    return sdk;
}