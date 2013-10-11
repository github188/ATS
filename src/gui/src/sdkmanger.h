#ifndef SDKMNG_H
#define SDKMNG_H

#include <list>
#include "sdk_layer.h"
#include "osa.h"
#include "device.h"


#ifdef __OSA_OS_WIN32__
#define SDK_DIR     "C:\\ats\\sdk_plugins\\"
#endif

#ifdef __OSA_OS_LINUX__
#define SDK_DIR     "/usr/lib/ats/sdk_plugins/"
#endif


namespace ATS
{

class SDKManger
{
public:
    SDKManger();

    osa_err_t   loadAllSDK();
    SDK_Layer   *devMatchSdk(Device *dev);

private:
    static std::list <SDK_Layer *> sdkList;
};

}


#endif // SDKMNG_H
