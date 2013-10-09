/**
 *  sdk.h
 *
 */


#ifndef __SDK_H__
#define __SDK_H__


#include "osa.h"
#include "conf.h"


typedef struct _ATS_SDK_INTERFACE
{
    osa_char_t      sdk_namespace[OSA_NAME_MAX];

    osa_err_t       (*init)();
    void            (*exit)();

} ATS_SDKLayer;


osa_err_t   ATS_SdkModuleInit(ATS_Conf *cf);
void        ATS_SdkModuleExit();


#endif
