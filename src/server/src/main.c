/*
 * cat_main.c
 *
 * Copyright (C) TuoAn
 *
 */


#include "osa.h"
#include "conf.h"
#include "module.h"
#include "test_drv.h"
#include "bus.h"
#include "data.h"
#include "test_event.h"

#include "test.h"
#include "report.h"
#include "erp.h"
#include "log.h"
#include "sys.h"
#include "dev_prober.h"


static ats_bus_t        dev_bus;
static ats_bus_ops_t    dev_bus_ops;
static ats_bus_t        tdrv_bus;
static ats_bus_ops_t    tdrv_bus_ops;
static ats_bus_t        sdk_bus;
static ats_bus_ops_t    sdk_bus_ops;


static void dev_bus_init();
static void tdrv_bus_init();
static void sdk_bus_init();


int main(int argc, char **argv)
{
    cf_log_t    logcf;
    if (xml_parse_log_conf(ATS_CONFIG_FILE, &logcf) != OSA_ERR_OK)
    {
        osa_log_error("Failed to parse log configuration file!\n");
        return -1;
    }
    
    if (ats_log_open(logcf.logfile) != OSA_ERR_OK)
    {
        osa_log_error("Failed to open log!\n");
        return -1;
    }
    
    dev_bus_init();
    tdrv_bus_init();
    sdk_bus_init();
    
    
    // 加载测试插件
    if (ats_tevent_plugin_load(TEST_POINT_PLUGIN) != OSA_ERR_OK)
    {
        ats_log_error("Failed to load TestPoint plug-in!\n");
        goto release;
    }

    // 加载SDK插件
    if (ats_sdk_plugin_load() != OSA_ERR_OK)
    {
        ats_log_error("Failed to load sdk plugin!\n");
        goto release;
    }
    
    // 加载系统中的测试驱动
    if (ats_tdrv_plugin_load(conf) != OSA_ERR_OK)
    {
        ats_log_error("Failed to load the driver for test!\n");
        goto release;
    }

    // 初始化测试模块
    if (ATS_TestModuleInit(conf) != OSA_ERR_OK)
    {
        ats_log_error("Failed to initialize <TEST> module!\n");
        goto release;
    }

    // 初始化报告模块
    if (ATS_ReportModuleInit(conf) != OSA_ERR_OK)
    {
        ats_log_error("Failed to initialize <REPORT> module!\n");
        goto release;
    }

    // 初始化ERP模块
    if (ATS_ErpModuleInit(conf) != OSA_ERR_OK)
    {
        ats_log_error("Failed to initialize <ERP> module!\n");
        goto release;
    }

    // 初始化设备探测模块
    if (ATS_DevProberModuleInit(conf) != OSA_ERR_OK)
    {
        ats_log_error("Failed to initialize <DEV_PROBER> module!\n");
        goto release;
    }

    // 初始化系统模块
    if (ATS_SysModuleInit(conf) != OSA_ERR_OK)
    {
        ats_log_error("Failed to initialize <SYS> module!\n");
        goto release;
    }

    // 初始化注册到系统中的所有模块
    ATS_ModuleInitAll(argc, argv);

    // 系统执行，处理消息循环
    ATS_SysExec();

    // 移除所有挂接到设备总线的测试驱动
    ATS_DevBusRemoveAllDrv();

    // 移除所有挂接到设备总线的设备
    ATS_DevBusRemoveAllDev();

    // 关闭配置文件
    ATS_ConfClose(conf);

    // 关闭日志文件
    ats_log_close();

    return 0;

release:
    ATS_DevBusRemoveAllDrv();
    ATS_DevBusRemoveAllDev();
    ATS_ConfClose(conf);
    ATS_LogClose();
    return -1;
}

static void dev_bus_init()
{
    dev_bus_ops.match = dev_bus_match;
    dev_bus_ops.remove = dev_bus_remove;
    
    ats_bus_register(&dev_bus, "device", &dev_bus_ops);
}

static void tdrv_bus_init()
{
    tdrv_bus_ops.match = dev_bus_match;
    tdrv_bus_ops.remove = dev_bus_remove;
    
    ats_bus_register(&tdrv_bus, "tdrv", &tdrv_bus_ops);
}

static void sdk_bus_init()
{
    sdk_bus_ops.match = dev_bus_match;
    sdk_bus_ops.remove = dev_bus_remove;
    
    ats_bus_register(&sdk_bus, "sdk", &sdk_bus_ops);
}

