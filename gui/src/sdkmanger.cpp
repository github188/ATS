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
    typedef SDK_Layer *(entryFunc);

    osa_dll_t sdkDll;
    osa_dir_t *dir;
    osa_dirent_t dent;
    char *sdkFile = NULL;
    entryFunc getSDK;

    if ((dir = osa_dir_open(SDK_DIR)) == NULL)
    {
        GUI_LogError("Failed to open SDK directory: %s!", SDK_DIR);
        return OSA_ERR_ERR;
    }

    while (osa_dir_read(dir, &dent) == OSA_ERR_OK)
    {
        sdkFile = dent.name;
        osa_assert(sdkFile != NULL);

        if (osa_dll_load(&sdkDll, sdkFile) != OSA_ERR_OK)
        {
            GUI_LogError("Failed to load SDK Plug-in : %s!", sdkFile);
            break;
        }
        else
        {
            GUI_LogInfo("Load SDK Plugin: %s\n", sdkFile);
        }

        if ((getSDK = (entryFunc)osa_dll_sym(&sdkDll, "SDK_PluginGet")) == NULL)
        {
            GUI_LogError("Can not found SDK entry!: %s\n", sdkFile);
            break;
        }
    }

    return OSA_ERR_OK;
}
