/**
 *  dev_prober.h
 *
 */

#ifndef __DEV_PROBER_H__
#define __DEV_PROBER_H__


#include "osa.h"
#include "conf.h"


#ifdef __cplusplus
extern "C"
{
#endif


typedef struct
{
    osa_uint8_t     dp_class;
} ATS_DevProberInfo;


typedef struct _ATS_DEV_PROBER
{
    osa_char_t          name[OSA_NAME_MAX];    // 名字
    ATS_DevProberInfo   info;

    void    (*probe)();     // 探测设备
    void    (*keepAlive)();     // 保活
} ATS_DevProber;



osa_err_t   ATS_DevProberModuleInit(ATS_Conf *cf);
void        ATS_DevProberModuleExit();


#ifdef __cplusplus
}
#endif

#endif
