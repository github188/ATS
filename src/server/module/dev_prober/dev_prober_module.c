/**
 *  dev_prober_module.c
 *
 */



#include "osa.h"
#include "module.h"
#include "conf_xml.h"
#include "log.h"
#include "module/dev_prober.h"


static osa_err_t   devprober_begin(ats_module_t *m, int argc, char **argv);
static void        devprober_end(ats_module_t *m);
static void        *devprober_routine(void *param);


static osa_thread_t     devprober_thread;
static ats_module_t     devprober_module;
static ats_mops_t       devprober_mops;


osa_err_t ats_devprober_mod_init()
{
    devprober_mops.begin = devprober_begin;
    devprober_mops.end = devprober_end;
    
    return ats_module_register(&devprober_module, "devprober", &devprober_mops);
}

void ats_devprober_mod_exit()
{
    ats_module_unregister("devprober");
}

static osa_err_t devprober_begin(ats_module_t *m, int argc, char **argv)
{
    // 创建设备探测线程
    osa_thread_init(&devprober_thread, "devprober_thread", devprober_routine, NULL);

    if (osa_thread_start(&devprober_thread) != OSA_ERR_OK)
    {
        ats_log_error("Failed to start device prober thread!\n");

        return OSA_ERR_ERR;
    }
}


static void devprober_end(ats_module_t *m)
{
    osa_thread_stop(&devprober_thread);
}


static void *devprober_routine(void *param)
{
    osa_bool_t  isExit = OSA_FALSE;

    extern ats_devprober_t      *g_devProberTable[];
    extern osa_uint32_t         g_devProberNum;
    ats_devprober_t             *node = NULL;
    int i;

    while (isExit != OSA_TRUE)
    {
        for (i=0; i<g_devProberNum; i++)
        {
            node = g_devProberTable[i];
            if (node->probe)
            {
                ats_log_info("Probing device with prober: (%s)\n", node->name);
                node->probe();
            }
        }

        osa_timer_delay(5, 0);
    }
}
