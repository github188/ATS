/*
 * dummy_test.c
 *
 * Copyright (C) TuoAn
 *
 */


#include "test_event.h"
#include "data.h"
#include "xml_parse.h"


#define     TEST_DEFAULT_PRIORITY       100


osa_err_t       dummyTestParseConf(ats_tevent_t *self, osa_char_t *cf);
ats_result_t  dummyTestStart(void *testCase);
osa_err_t       dummyBegin(ats_tevent_t *self);
void            dummySuccessCall(ats_tevent_t *self);
void            dummyFailedCall(ats_tevent_t *self);
void            dummyEnd(ats_tevent_t *self);

ats_tevent_t   dummyTestEvent=
{
    .name       = "DummyTest",
    .attr =
    {
        .proi   = TEST_DEFAULT_PRIORITY,
    },
    .ops =
    {
        .init       = dummy_init,
        .test_start = dummyTestStart,
        .test_stop  = NULL,
        .suss_cb    = dummySuccessCall,
        .fail_cb    = dummyFailedCall,
        .fini       = dummyEnd,
    },
};


ats_result_t  dummyTestStart(void *testCase)
{
    TP_LogInfo("start test dummy module!\n");

    TEST_Dummy  *d = (TEST_Dummy *)testCase;

    printf("in : %s, out: %s\n", d->dummyIn, d->dummyExpOut);

    return ATS_TEST_SUCCESS;
}


void    dummySuccessCall(ats_tevent_t *self)
{
    TP_LogInfo("dummy test success call!\n");
}


void    dummyFailedCall(ats_tevent_t *self)
{
    TP_LogInfo("dummy test failed call!\n");

}


osa_err_t   dummyTestParseConf(ats_tevent_t *self, osa_char_t *cf)
{
    dummyTestParse(self, cf);
    return OSA_ERR_OK;
}


osa_err_t   dummyBegin(ats_tevent_t *self)
{
    printf("----------------------------BEGIN----------------------------------------\n");
    return OSA_ERR_OK;
}

void    dummyEnd(ats_tevent_t *self)
{

    printf("----------------------------END------------------------------------------\n");
    osa_uint32_t allTimes = self->statistic.testTimes;
    osa_uint32_t failTimes = self->statistic.failedTimes;

    osa_char_t buf[1024]  = {0};

    sprintf(buf, "[%s] Test Times: %d, Fail Times: %d, Fail Rate: %.2f%%", self->name, allTimes, failTimes, failTimes/(allTimes *1.0)*100);

    self->report->write(self->report, buf, sizeof(buf));
}
