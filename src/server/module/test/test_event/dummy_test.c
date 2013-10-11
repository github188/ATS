/*
 * dummy_test.c
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


osa_err_t       dummyTestParseConf(ATS_TestEvent *self, osa_char_t *cf);
ATS_TestResult  dummyTestStart(void *testCase);
osa_err_t       dummyBegin(ATS_TestEvent *self);
void            dummySuccessCall(ATS_TestEvent *self);
void            dummyFailedCall(ATS_TestEvent *self);
void            dummyEnd(ATS_TestEvent *self);

ATS_TestEvent   dummyTestEvent=
{
    .name       = "DummyTest",
    .priority   = TEST_DEFAULT_PRIORITY,
    .parseConf  = dummyTestParseConf,
    .begin      = dummyBegin,
    .startTest  = dummyTestStart,
    .stopTest   = NULL,
    .successFunc= dummySuccessCall,
    .failedFunc = dummyFailedCall,
    .end        = dummyEnd,
};


ATS_TestResult  dummyTestStart(void *testCase)
{
    TP_LogInfo("start test dummy module!\n");

    TEST_Dummy  *d = (TEST_Dummy *)testCase;

    printf("in : %s, out: %s\n", d->dummyIn, d->dummyExpOut);

    return ATS_TEST_SUCCESS;
}


void    dummySuccessCall(ATS_TestEvent *self)
{
    TP_LogInfo("dummy test success call!\n");
}


void    dummyFailedCall(ATS_TestEvent *self)
{
    TP_LogInfo("dummy test failed call!\n");

}


osa_err_t   dummyTestParseConf(ATS_TestEvent *self, osa_char_t *cf)
{
    dummyTestParse(self, cf);
    return OSA_ERR_OK;
}


osa_err_t   dummyBegin(ATS_TestEvent *self)
{
    printf("----------------------------BEGIN----------------------------------------\n");
    return OSA_ERR_OK;
}

void    dummyEnd(ATS_TestEvent *self)
{

    printf("----------------------------END------------------------------------------\n");
    osa_uint32_t allTimes = self->statistic.testTimes;
    osa_uint32_t failTimes = self->statistic.failedTimes;

    osa_char_t buf[1024]  = {0};

    sprintf(buf, "[%s] Test Times: %d, Fail Times: %d, Fail Rate: %.2f%%", self->name, allTimes, failTimes, failTimes/(allTimes *1.0)*100);

    self->report->write(self->report, buf, sizeof(buf));
}
