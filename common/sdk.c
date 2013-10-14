/**
 *  sdk.c
 *
 */

#include "osa.h"
#include "core.h"


#define PLUGIN_MAX  10

struct sdk_plugin
{
    osa_dll_t   dll;
    ats_sdk_t   *sdk;
};

static struct sdk_plugin plugins[PLUGIN_MAX];


ats_sdk_t   *ats_sdk_plugin_load(const osa_char_t *plugin_file)
{
    if (!plugin_file)
    {
        return NULL;
    }

    typedef ats_sdk_t *(*sdk_get)(void);

    ats_sdk_t   *sdk = NULL;
    void        *p = NULL;
    sdk_get     getsdk = NULL;
    osa_uint32_t i;

    do
    {
        for (i=0; i<PLUGIN_MAX; i++)
        {
            if (!plugins[i].sdk)
            {
                break;
            }
        }
        if (i == PLUGIN_MAX)
        {
            ats_log_error("SDK max!\n");
            break;
        }

        if (osa_dll_load(&plugins[i].dll, plugin_file) != OSA_ERR_OK)
        {
            ats_log_error("Failed to load sdk plugin:%s\n", plugin_file);
            break;
        }

        if ((p = osa_dll_sym(&plugins[i].dll, "SDK_PluginGet")) == NULL)
        {
            ats_log_error("Can not find the entry for sdk plugin: %s\n", plugin_file);
            break;
        }

        getsdk = (sdk_get)p;

        sdk = getsdk();
        if (!sdk)
        {
            ats_log_error("Can not get sdk object!\n");
            break;
        }
        plugins[i].sdk = sdk;
    } while(0);

    return sdk;
}

void ats_sdk_plugin_unload(ats_sdk_t *sdk)
{
    ats_bus_t *sdk_bus = ats_bus_find("sdk_bus");
    if (!sdk_bus)
    {
        ats_log_error("No sdk bus found!\n");
        return;
    }

    osa_uint32_t i;

    for (i=0; i<PLUGIN_MAX; i++)
    {
        if (plugins[i].sdk && plugins[i].sdk == sdk)
        {
            ats_log_info("Unload device(%s) sdk\n", sdk->dev->name);

            sdk->dev->sdk = NULL;
            osa_dll_unload(&plugins[i].dll);
            plugins[i].sdk = NULL;
        }
    }
}
