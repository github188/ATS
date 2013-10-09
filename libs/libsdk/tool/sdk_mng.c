/**
 *  sdk_mng.c
 *
 */


#include "sdk_layer.h"
#include "sdk_log.h"
#include "osa.h"


#ifdef __cplusplus
extern "C"
{
#endif


static osa_list_t   sdkListHead = {&sdkListHead, &sdkListHead};


SDK_Layer   *SDK_Find(const osa_char_t *nameSpace)
{
    osa_assert(nameSpace != NULL);

    SDK_Layer   *node = NULL;
    osa_list_t  *l = NULL;

    for (l = sdkListHead.next; l != &sdkListHead; l = l->next)
    {
        node = osa_list_entry(l, SDK_Layer, list);

        if (!strcmp(node->nameSpace, nameSpace))
        {
            return node;
        }
    }

    return NULL;
}


osa_err_t   SDK_Register(SDK_Layer *sdk)
{
    osa_assert(sdk != NULL);

    SDK_Layer   *p = NULL;

    if ((p = SDK_Find(sdk->nameSpace)) != NULL)
    {
        SDK_LogWarn("Replace SDK: nameSpace(%s)\n", sdk->nameSpace);
        p = sdk;
    }
    else
    {
        osa_list_insert_before(sdkListHead.next, &sdk->list);
    }

    return OSA_ERR_OK;
}


void        SDK_Unreigster(const osa_char_t *nameSpace)
{
    osa_assert(nameSpace != NULL);

    SDK_Layer *p = NULL;

    if ((p = ATS_DevBusFindDrv(nameSpace)) != NULL)
    {
        SDK_LogInfo("Unregister SDK: nameSpace(%s)\n", nameSpace);

        osa_list_remove(&p->list);
    }

    return OSA_ERR_OK;
}


osa_err_t   SDK_MngInit()
{

}


void        SDK_MngExit()
{

}


osa_err_t   SDK_MngLoadSDK(const osa_char_t *sdkLib)
{
    osa_assert(sdkLib != NULL);

    osa_dll_t   dll;

    if (osa_dll_load(&dll, sdkLib) != OSA_ERR_OK)
    {
        SDK_LogError("Failed to load SDK Plugin!\n");
        return OSA_ERR_ERR;
    }

    typedef void (*entryFunc)(void);
    typedef void (*exitFunc)(void);

    entryFunc   entry;
    exitFunc    exit;

    entry   = (entryFunc)osa_dll_sym(&dll, "SDK_PluginInit");
    exit    = (exitFunc)osa_dll_sym(&dll, "SDK_PluginExit");

    if (!entry || !exit)
    {
        SDK_LogError("No entry or exit function found in library: %s\n", sdkLib);
        return OSA_ERR_ERR;
    }

    entry();

    return OSA_ERR_OK;
}


#ifdef __cplusplus
}
#endif
