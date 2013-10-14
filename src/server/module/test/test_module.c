/**
 * test.c
 *
 */

#include "osa.h"
#include "core.h"
#include "xml.h"
#include "config.h"
#include "test_event.h"
#include "module/test.h"


static ats_module_t     test_module;
static ats_mops_t       test_mops;


static osa_err_t    test_begin(ats_module_t *m, int argc, char **argv);
static void         test_end(ats_module_t *m);
static osa_err_t    load_sdk_plugins();
static void         unload_sdk_plugins();


osa_err_t ats_test_mod_init()
{
    if (ats_tevent_plugin_load(ATS_TEST_EVENT_PLUGIN) != OSA_ERR_OK)
    {
        ats_log_error("Failed to load the test event plugin!\n");
    }
    else
    {
        ats_log_info("The test event plugin loaded!\n");
    }

    test_mops.begin = test_begin;
    test_mops.end   = test_end;

    test_module.conf_file = ATS_CONFIG_FILE;

    return ats_module_register(&test_module, "test", &test_mops);
}

void ats_test_mod_exit()
{
    ats_tevent_plugin_unload();
    ats_module_unregister("test");
}


static osa_err_t test_begin(ats_module_t *m, int argc, char **argv)
{
    return OSA_ERR_OK;
}

static void test_end(ats_module_t *m)
{
}
