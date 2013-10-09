/*
 * cat_erp.h
 *
 * Copyright (C) TuoAn
 *
 */

#ifndef ATS_ERP_H_
#define ATS_ERP_H_


#include "osa.h"
#include "conf.h"


typedef struct _ATS_ERP_INTERFACE
{
    // 初始化ERP
    osa_err_t       (*init)();
    // 退出ERP
    void            (*exit)();
    // 连接ERP系统
    void            *(*connect)(const char *erpFile, osa_uint32_t timeout);
    // 断开ERP系统
    osa_uint8_t     (*disconnect)(void *erpFd);
    // 向erp发送数据
    osa_err_t       (*send)(void *erpFd, void *data, osa_size_t size);

} ATS_Erp;


osa_err_t   ATS_ErpModuleInit(ATS_Conf *cf);

#endif /* ATS_ERP_H_ */
