/**
 *  agent.h
 *
 */


#ifndef __SYS_H__
#define __SYS_H__


#include "osa.h"
#include "conf.h"

// 系统支持的命令
enum
{
    SYS_CMD_MIN = 0,

    SYS_CMD_LOGIN,              // 登陆: SYS:Login
    SYS_CMD_EXIT,               // 退出: SYS:Exit
    SYS_CMD_GET_DEVS,           // 获取待测设备列表: SYS:GetDevs

    SYS_CMD_MAX,
};


osa_err_t   ATS_SysModuleInit(ATS_Conf *cf);
void        ATS_SysModuleExit();

void        ATS_SysInit();
void        ATS_SysExec();

// 探测所有待测设备
void        ATS_SysProbeDevs();

#endif
