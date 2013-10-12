/*
 * dummy_test.c
 *
 * Copyright (C) TuoAn
 *
 */



#include "xml_parse.h"
#include "test_event.h"
#include "data.h"
#include "log.h"
#include "module/report.h"


static osa_err_t       dummy_init(ats_tevent_t *self);
static ats_result_t    dummy_test_start(void *testCase);
static void            dummy_suss_cb(ats_tevent_t *self);
static void            dummy_fail_cb(ats_tevent_t *self);
static void            dummy_fini(ats_tevent_t *self);


ats_tevent_t   dummy_test_event=
{
    .name       = "DummyTest",
    .ops =
    {
        .init       = dummy_init,
        .test_start = dummy_test_start,
        .test_stop  = NULL,
        .suss_cb    = dummy_suss_cb,
        .fail_cb    = dummy_fail_cb,
        .fini       = dummy_fini,
    },
};


static osa_err_t dummy_init(ats_tevent_t *self)
{
    return OSA_ERR_OK;
}

ats_result_t dummy_test_start(void *testCase)
{
    ats_log_info("start test dummy module!\n");

    TEST_Dummy  *d = (TEST_Dummy *)testCase;

    printf("in : %s, out: %s\n", d->dummyIn, d->dummyExpOut);

    return ATS_SUCCEED;
}


void dummy_suss_cb(ats_tevent_t *self)
{
    ats_log_info("dummy test success call!\n");
}


static void dummy_fail_cb(ats_tevent_t *self)
{
    ats_log_info("dummy test failed call!\n");

}


static void dummy_fini(ats_tevent_t *self)
{
    osa_uint32_t all_times = self->attr.stat.test_times;
    osa_uint32_t fail_times = self->attr.stat.fail_times;
    osa_double_t fail_rate = (all_times == 0)? 0: (fail_times/(all_times *1.0)*100);

    osa_char_t buf[1024]  = {0};

    sprintf(buf, "[%s] Test Times: %d, Fail Times: %d, Fail Rate: %.2f%%", 
                self->name, all_times, fail_times, fail_rate);

    ats_report_write(self->report, buf, sizeof(buf));
}
