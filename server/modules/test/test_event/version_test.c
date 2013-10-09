/*
 * version_test.c
 *
 * Copyright (C) TuoAn
 *
 */


#include "test_event.h"
#include "data.h"
#include "ats.h"
#include "_log.h"
#include "xml_parse.h"


#define     TEST_DEFAULT_PRIORITY       100


osa_err_t       versionTestParseConf(ATS_TestEvent *self, osa_char_t *cf);
ATS_TestResult  versionTestStart(void *testCase);
osa_err_t       versionBegin(ATS_TestEvent *self);
void            versionSuccessCall(ATS_TestEvent *self);
void            versionFailedCall(ATS_TestEvent *self);
void            versionEnd(ATS_TestEvent *self);

ATS_TestEvent   versionTestEvent=
{
    .name       = "VersionTest",
    .priority   = TEST_DEFAULT_PRIORITY,
    .parseConf  = versionTestParseConf,
    .begin      = versionBegin,
    .startTest  = versionTestStart,
    .stopTest   = NULL,
    .successFunc= versionSuccessCall,
    .failedFunc = versionFailedCall,
    .end        = NULL,
};


ATS_TestResult  versionTestStart(void *testCase)
{
    TP_LogInfo("start VERSION_TEST !\n");

    return ATS_TEST_SUCCESS;
}


void    versionSuccessCall(ATS_TestEvent *self)
{
    TP_LogInfo("version test success call!\n");
}


void    versionFailedCall(ATS_TestEvent *self)
{
    TP_LogInfo("version test failed call!\n");

}


osa_err_t   versionTestParseConf(ATS_TestEvent *self, osa_char_t *cf)
{
    return OSA_ERR_OK;
}


osa_err_t   versionBegin(ATS_TestEvent *self)
{
    return OSA_ERR_OK;
}

void    versionEnd(ATS_TestEvent *self)
{
    osa_uint32_t allTimes = self->statistic.testTimes;
    osa_uint32_t failTimes = self->statistic.failedTimes;

    osa_char_t buf[1024]  = {0};

    //sprintf(buf, "[%s] 测试总次数: %d, 失败次数: %d, 失败率: %.2f%%", self->name, allTimes, failTimes, failTimes/(allTimes *1.0)*100);

    //self->report->write(self->report, buf, sizeof(buf));
}
