/*
 * cat_test.h
 *
 * Copyright (C) TuoAn
 *
 */

#ifndef ATS_TEST_POINT_H_
#define ATS_TEST_POINT_H_


#include "osa.h"
#include "ats.h"
#include "report.h"
#include "conf.h"


#ifdef __cplusplus
extern "C" {
#endif


typedef enum
{
    ATS_TEST_SUCCESS = 0,
    ATS_TEST_FAILED = -1,
}
ATS_TestResult;


// 测试用例容器
struct _ATS_TEST_CASE_BOX
{
    osa_uint32_t        caseNum;                // 测试用例数量
    osa_uint32_t        caseSize;               // 每个测试用例大小
    void                *privData;              // 测试用例数据地址
};


// 测试统计
typedef struct _ATS_TEST_STATISTIC
{
    osa_uint32_t        testTimes;              // 总共测试次数
    osa_uint32_t        failedTimes;            // 失败次数
} ATS_TestStatistic;


// 测试点
struct _ATS_TEST_EVENT
{
    char                *name;          // 测试点名字
    osa_uint32_t        priority;       // 测试优先级，数字越小优先级越大
    ATS_TestCaseBox     testCaseBox;    // 测试用例容器
    ATS_TestResult      result;         // 测试结果
    ATS_TestStatistic   statistic;      // 结果统计
    ATS_Report          *report;        // report

    osa_list_t          list;           // 链表

    osa_err_t       (*parseConf)(ATS_TestEvent *self, osa_char_t *cf);
    osa_err_t       (*begin)(ATS_TestEvent *self);       // 开始，每个测试点调用一次
    ATS_TestResult  (*startTest)(void *testCase);        // 启动测试,每个测试用例调用一次，每个测试点可能调用多次
    void            (*stopTest)();                       // 停止测试, 现在没有使用
    void            (*successFunc)(ATS_TestEvent *self); // 测试成功后调用,每个测试用例调用一次，每个测试点可能调用多次
    void            (*failedFunc)(ATS_TestEvent *self);  // 测试失败后调用,每个测试用例调用一次，每个测试点可能调用多次
    void            (*end)(ATS_TestEvent *self);         // 结束,每个测试点调用一次
};


ATS_TestEvent   *ATS_TestEventFind(const osa_char_t *name);


#ifdef __cplusplus
}
#endif

#endif /* ATS_TEST_H_ */
