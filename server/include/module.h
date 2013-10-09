/*
 * module.h
 *
 * Copyright (C) TuoAn
 *
 */

#ifndef MODULE_H_
#define MODULE_H_

#include "osa.h"
#include "ats.h"

#ifdef __cplusplus
extern "C" {
#endif

enum
{
    ATS_MODULE_OFF = 0,
    ATS_MODULE_ON = 1,
};


struct _ATS_MODULE_CONF_OPS
{
    ATS_Conf    *(*open)(const char *file);                            // 打开模块配置文件
    void        (*close)(ATS_Conf *cf);                         // 关闭模块配置文件
    osa_err_t   (*read)(ATS_Conf *cf, void *out_data);          // 读取配置文件
    osa_err_t   (*write)(ATS_Conf *cf, void *data);             // 写配置文件
    osa_err_t   (*ctrl)(ATS_Conf *cf, osa_uint32_t cmd, void *arg);     // 控制
};



struct _ATS_MODULE
{
    // 模块名字
    char                name[OSA_NAME_MAX];
    // 模块状态，ON或者OFF
    osa_uint8_t         state;
    // 配置文件
    ATS_Conf            *cf;
    // 模块配置文件接口
    ATS_ModuleConfOps   cfops;
    // 模块入口
    osa_err_t           (*entry)(ATS_Conf *conf, int argc, char **argv);
    // 模块出口
    void                (*exit)(ATS_Conf *conf);
};

#define ATS_MODULE_MAX      10

ATS_Module      *ATS_ModuleFind(const char *name);
osa_err_t       ATS_ModuleRegister(ATS_Module *module);
osa_err_t       ATS_ModuleUnregister(ATS_Module *module);

void            ATS_ModuleInitAll(int argc, char **argv);

#ifdef __cplusplus
}
#endif

#endif /* MODULE_H_ */
