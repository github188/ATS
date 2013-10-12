/*
 * test.c
 *
 * Copyright (C) TuoAn
 *
 */

#include "osa.h"
#include "module.h"
#include "conf_xml.h"
#include "log.h"
#include "module/test.h"
#include "test_event.h"
#include "sdk.h"
#include "test_drv.h"
#include "config.h"


static ats_module_t     test_module;
static ats_mops_t       test_mops;


osa_err_t   test_begin(ats_module_t *m, int argc, char **argv);
void        test_end(ats_module_t *m);


osa_err_t ats_test_mod_init()
{
    if (ats_tevent_plugin_load(ATS_TEST_EVENT_PLUGIN) != OSA_ERR_OK)
    {
        ats_log_error("Failed to load TestPoint plug-in!\n");
    }

#if 0
    if (ats_sdk_plugin_load() != OSA_ERR_OK)
    {
        ats_log_error("Failed to load sdk plugin!\n");
    }
#endif
    
    xml_parse_dev_conf(ATS_CONFIG_FILE);

    test_mops.begin = test_begin;
    test_mops.end   = test_end;
    
    test_module.conf_file = ATS_CONFIG_FILE;
    
    return ats_module_register(&test_module, "test", &test_mops);
}

void ats_test_mod_exit()
{
    ats_module_unregister("test");
}


osa_err_t   test_begin(ats_module_t *m, int argc, char **argv)
{
    return OSA_ERR_OK;
}

void        test_end(ats_module_t *m)
{

}

