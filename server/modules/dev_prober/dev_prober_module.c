/**
 *  dev_prober_module.c
 *
 */



#include "osa.h"
#include "module.h"
#include "ats.h"
#include "conf_xml.h"
#include "log.h"
#include "dev_prober.h"


static osa_thread_t dpThread;


static osa_err_t   devProberModuleEntry(ATS_Conf *cf, int argc, char **argv);
static void        devProberModuleExit(ATS_Conf *cf);
static void        *devProberFunc(void *param);


static ATS_Module  devProberModule =
{
    .name   = "devProber",
    .state  = ATS_MODULE_ON,
    .cfops     =
    {
        .open   = NULL,
        .close  = NULL,
        .read   = NULL,
        .write  = NULL,
        .ctrl   = NULL,
    },
    .entry  = devProberModuleEntry,
    .exit   = devProberModuleExit,
};



osa_err_t   ATS_DevProberModuleInit(ATS_Conf *cf)
{
    devProberModule.cf = cf;

    ATS_ModuleRegister(&devProberModule);

    return OSA_ERR_OK;
}


void        ATS_DevProberModuleExit()
{
    ATS_ModuleUnregister(&devProberModule);
}


static osa_err_t   devProberModuleEntry(ATS_Conf *cf, int argc, char **argv)
{
    // 创建设备探测线程
    osa_thread_init(&dpThread, "DevProber", devProberFunc, NULL);

    if (osa_thread_start(&dpThread) != OSA_ERR_OK)
    {
        ATS_LogError("Failed to start device prober thread!\n");

        return OSA_ERR_ERR;
    }
}


static void    devProberModuleExit(ATS_Conf *cf)
{
    osa_thread_stop(&dpThread);
}


static void *devProberFunc(void *param)
{
    osa_bool_t  isExit = OSA_FALSE;

    extern ATS_DevProber    *g_devProberTable[];
    extern osa_uint32_t     g_devProberNum;
    ATS_DevProber           *node = NULL;
    int i;

    while (isExit != OSA_TRUE)
    {
        for (i=0; i<g_devProberNum; i++)
        {
            node = g_devProberTable[i];
            if (node->probe)
            {
                ATS_LogInfo("Probing device with prober: (%s)\n", node->name);
                node->probe();
            }
        }

        osa_timer_delay(5, 0);
    }
}
