/**
 *  dev_prober_module.c
 *
 */



#include "osa.h"
#include "core.h"
#include "xml.h"
#include "config.h"
#include "module/dev_prober.h"


static osa_err_t   devpb_begin(ats_module_t *m, int argc, char **argv);
static void        devpb_end(ats_module_t *m);
static void        *devpb_routine(void *param);


static osa_thread_t     devpb_thread;
static ats_module_t     devpb_module;
static ats_mops_t       devpb_mops;
static osa_cond_t       exit_cond;
static osa_bool_t       flag = OSA_FALSE;


osa_err_t ats_devpb_mod_init()
{
    devpb_mops.begin = devpb_begin;
    devpb_mops.end = devpb_end;

    devpb_module.conf_file = ATS_CONFIG_FILE;

    return ats_module_register(&devpb_module, "devpb", &devpb_mops);
}

void ats_devpb_mod_exit()
{
    ats_module_unregister("devpb");
}

static osa_err_t devpb_begin(ats_module_t *m, int argc, char **argv)
{
    // 创建设备探测线程
    osa_thread_init(&devpb_thread, "devpb_thread", devpb_routine, NULL);

    if (osa_thread_start(&devpb_thread) != OSA_ERR_OK)
    {
        ats_log_error("Failed to start device prober thread!\n");

        return OSA_ERR_ERR;
    }

    return OSA_ERR_OK;
}

static void devpb_end(ats_module_t *m)
{
    //osa_cond_signal(&exit_cond);
    flag = OSA_TRUE;
    osa_thread_exit();
}

static void *devpb_routine(void *param)
{
    //osa_timespec_t timeout;
    //osa_cond_init(&exit_cond);

    ats_devpb_init();
    
    while (flag != OSA_TRUE)
    {
        //timeout.tv_sec = 5;
        //timeout.tv_nsec = 0;
        
        ats_devpb_probe();

		osa_timer_delay(5, 0);

        //osa_cond_wait(&exit_cond, &timeout);
    }
    
    //osa_cond_fini(&exit_cond);
    //osa_thread_exit();

	return NULL;
}
