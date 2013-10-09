/**
 *  test_drv.h
 *
 */


#ifndef __TEST_DRV_H__
#define __TEST_DRV_H__

#include "ats.h"
#include "osa.h"
#include "test_event.h"
#include "report.h"


#ifdef __cplusplus
extern "C" {
#endif


// 测试驱动
struct _ATS_TEST_DRIVER
{
    osa_char_t      name[OSA_NAME_MAX];     // 测试驱动名称
    osa_char_t      cf[OSA_NAME_MAX];       // 配置文件
    osa_list_t      list;                   // 链表
    osa_list_t      teListHead;             // (test point list)测试点集合链表头节点
    ATS_Report      report;                 // 报告

    osa_err_t       (*remove)(ATS_TestDrv *self);   // 移除操作
};


ATS_TestDrv     *ATS_TestDrvNew(const osa_char_t *name, const osa_char_t *cf);
void            ATS_TestDrvDelete(ATS_TestDrv *tdv);


ATS_TestEvent   *ATS_TestDrvFindTestEvent(ATS_TestDrv *tdv, const char *name);
osa_err_t       ATS_TestDrvRegisterTestEvent(ATS_TestDrv *tdv, ATS_TestEvent *tp);
osa_err_t       ATS_TestDrvUnregisterTestEvent(ATS_TestDrv *tdv, const char *name);

osa_err_t       ATS_TestDrvLoad();

void            ATS_TestDrvDoTest(ATS_TestDrv *drv);

osa_err_t       ATS_TestDrvParseConf(ATS_TestDrv *drv);


#ifdef __cplusplus
}
#endif

#endif
