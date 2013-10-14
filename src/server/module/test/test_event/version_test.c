/*
 * version_test.c
 *
 * Copyright (C) TuoAn
 *
 */


#include "test_event.h"
#include "xml_parse.h"
#include "data.h"
#include "log.h"
#include "module/report.h"


static osa_err_t       version_init(ats_tevent_t *self);
static ats_result_t    version_test_start(void *testCase);
static void            version_suss_cb(ats_tevent_t *self);
static void            version_fail_cb(ats_tevent_t *self);
static void            version_fini(ats_tevent_t *self);


ats_tevent_t   version_test_event=
{
    .name       = "VersionTest",
    .ops        =
    {
        .init       = version_init,
        .test_start = version_test_start,
        .test_stop  = NULL,
        .suss_cb    = version_suss_cb,
        .fail_cb    = version_fail_cb,
        .fini       = version_fini,
    },
};



static osa_err_t version_init(ats_tevent_t *self)
{
    return OSA_ERR_OK;
}

ats_result_t version_test_start(void *testCase)
{
    ats_log_info("start test version!\n");
    return ATS_SUCCEED;
}


void version_suss_cb(ats_tevent_t *self)
{
    ats_log_info("version test success call!\n");
}


static void version_fail_cb(ats_tevent_t *self)
{
    ats_log_info("version test failed call!\n");
}


static void version_fini(ats_tevent_t *self)
{
    osa_uint32_t all_times = self->attr.stat.test_times;
    osa_uint32_t fail_times = self->attr.stat.fail_times;
    osa_double_t fail_rate = (all_times == 0)? 0: (fail_times/(all_times *1.0)*100);

    osa_char_t buf[1024]  = {0};

    sprintf(buf, "[%s] Test Times: %d, Fail Times: %d, Fail Rate: %.2f%%",
            self->name, all_times, fail_times, fail_rate);

    ats_report_write(self->report, buf, sizeof(buf));
}
