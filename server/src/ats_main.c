/*
 * cat_main.c
 *
 * Copyright (C) TuoAn
 *
 */


#include "osa.h"
#include "conf.h"
#include "conf_data.h"
#include "module.h"
#include "ats.h"
#include "test_drv.h"
#include "dev_bus.h"

#include "test.h"
#include "report.h"
#include "erp.h"
#include "log.h"
#include "sys.h"
#include "dev_prober.h"



int main(int argc, char **argv)
{
    // 打开配置文件
    ATS_Conf *conf = ATS_ConfOpen(ATS_CONFIG_FILE);
    if (!conf)
    {
        ATS_LogError("Failed to open configuration file!\n");
        return -1;
    }

    // 打开日志文件
    if (ATS_LogOpen(conf) != OSA_ERR_OK)
    {
        ATS_LogError("Failed to open log file!\n");
        ATS_ConfClose(conf);
        return -1;
    }

    // 加载测试插件
    if (ATS_TestLoadPlugin() != OSA_ERR_OK)
    {
        ATS_LogError("Failed to load TestPoint plug-in!\n");
        goto release;
    }

    // 初始化设备总线
    if (ATS_DevBusInit() != OSA_ERR_OK)
    {
        ATS_LogError("Failed to initialize the bus of device!\n");
        goto release;
    }

    // 加载系统中的测试驱动
    if (ATS_TestDrvLoad(conf) != OSA_ERR_OK)
    {
        ATS_LogError("Failed to load the driver for test!\n");
        goto release;
    }

    // 初始化测试模块
    if (ATS_TestModuleInit(conf) != OSA_ERR_OK)
    {
        ATS_LogError("Failed to initialize <TEST> module!\n");
        goto release;
    }

    // 初始化报告模块
    if (ATS_ReportModuleInit(conf) != OSA_ERR_OK)
    {
        ATS_LogError("Failed to initialize <REPORT> module!\n");
        goto release;
    }

    // 初始化ERP模块
    if (ATS_ErpModuleInit(conf) != OSA_ERR_OK)
    {
        ATS_LogError("Failed to initialize <ERP> module!\n");
        goto release;
    }

    // 初始化设备探测模块
    if (ATS_DevProberModuleInit(conf) != OSA_ERR_OK)
    {
        ATS_LogError("Failed to initialize <DEV_PROBER> module!\n");
        goto release;
    }

    // 初始化系统模块
    if (ATS_SysModuleInit(conf) != OSA_ERR_OK)
    {
        ATS_LogError("Failed to initialize <SYS> module!\n");
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
    ATS_LogClose();

    return 0;

release:
    ATS_DevBusRemoveAllDrv();
    ATS_DevBusRemoveAllDev();
    ATS_ConfClose(conf);
    ATS_LogClose();
    return -1;
}
