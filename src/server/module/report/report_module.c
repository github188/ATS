/*
 * report.c
 *
 * Copyright (C) TuoAn
 *
 */

#include "osa.h"
#include "core.h"
#include "xml.h"
#include "config.h"
#include "module/report.h"



static osa_err_t report_begin(ats_module_t *m, int argc, char **argv);
static void     report_end(ats_module_t *m);

static ats_module_t     report_module;
static ats_mops_t       report_ops;


osa_err_t ats_report_mod_init()
{
    report_ops.begin = report_begin;
    report_ops.end = report_end;

    report_module.conf_file = ATS_CONFIG_FILE;

    return ats_module_register(&report_module, "report", &report_ops);
}

void ats_report_mod_exit()
{
    ats_module_unregister("report");
}

static osa_err_t report_begin(ats_module_t *m, int argc, char **argv)
{
    cf_report_t reportcf;

    if (xml_parse_report_conf(m->conf_file, &reportcf) != OSA_ERR_OK)
    {
        ats_log_error("Failed to parse configuration file!\n");
        return OSA_ERR_ERR;
    }

}

static void report_end(ats_module_t *m)
{
}
