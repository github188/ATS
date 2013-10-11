#include "sdkmanger.h"
#include "string"

#include "log.h"

using namespace std;

using namespace  ATS;


list <SDK_Layer *> SDKManger::sdkList;

SDKManger::SDKManger()
{

}

osa_err_t SDKManger::loadAllSDK()
{
    typedef SDK_Layer *(*entryFunc)(void);

    osa_dll_t       sdkDll;
    osa_dir_t       *dir;
    osa_dirent_t    dent;
    entryFunc       getSDK;
    SDK_Layer       *sdk = NULL;
    osa_char_t      dllFile[FILENAME_MAX+1] = {0};

    if ((dir = osa_dir_open(SDK_DIR)) == NULL)
    {
        GUI_LogError("Failed to open SDK directory: %s!", SDK_DIR);
        return OSA_ERR_ERR;
    }

    while (osa_dir_read(dir, &dent) == OSA_ERR_OK)
    {
        // ignore directory
        if (!(dent.ft & OSA_FT_ARCHIVE))
        {
            continue;
        }

        if (strcmp(osa_file_suffix(dent.name), ".dll"))
        {
            continue;
        }

        osa_mem_zero(dllFile, sizeof(dllFile));
        strncpy(dllFile, SDK_DIR, strlen(SDK_DIR));
        strcat(dllFile, dent.name);

        if (osa_dll_load(&sdkDll, dllFile) != OSA_ERR_OK)
        {
            GUI_LogError("Failed to load SDK Plug-in : %s!\n", dent.name);
            continue;
        }

        GUI_LogInfo("Load SDK Plugin: %s\n", dent.name);
        if ((getSDK = (entryFunc)osa_dll_sym(&sdkDll, "SDK_PluginGet")) == NULL)
        {
            GUI_LogError("Can not found SDK entry!: %s\n", dent.name);
            continue;
        }

        if ((sdk = getSDK()) != NULL)
        {
            GUI_LogInfo("Found SDK : name(%s), version(%d), info(%s)\n",
                        sdk->nameSpace, sdk->version, sdk->info);
            sdkList.push_back(sdk);
        }
    }

    return OSA_ERR_OK;
}

SDK_Layer *SDKManger::devMatchSdk(Device *dev)
{
    if (!dev)
    {
        return NULL;
    }

    list <SDK_Layer *>::iterator itr;
    SDK_Layer *sdk = NULL;

    for (itr = sdkList.begin(); itr != sdkList.end(); itr++)
    {
        sdk = (*itr);
        if (!strcmp(sdk->nameSpace, dev->getSdkNameSpace().c_str()))
        {
            return sdk;
        }
    }

    return NULL;
}
