/**
 *  sdk_mng.h
 *
 */


#ifndef __SDK_MNG_H__
#define __SDM_MNG_H__


#include "osa.h"
#include "sdk_layer.h"


#ifdef __cplusplus
extern "C"
{
#endif


osa_err_t   SDK_MngInit();
void        SDK_MngExit();

// 加载SDK插件
osa_err_t   SDK_MngLoadSDK(const osa_char_t *sdkLib);

// 查找SDK
SDK_Layer   *SDK_Find(const osa_char_t *nameSpace);
// 注册SDK
osa_err_t   SDK_Register(SDK_Layer *sdk);
// 卸载SDK
void        SDK_Unreigster(const osa_char_t *nameSpace);


#ifdef __cplusplus
}
#endif


#endif