/**
 *  device.h
 *
 */


#ifndef __DEVICE_H__
#define __DEVICE_H__


#include "ats.h"
#include "osa.h"
#include "test_drv.h"


typedef struct _ATS_DEVICE_INFO
{
    osa_char_t      ip[20];       // 设备的IP地址
    osa_uint32_t    port;         // 设备的端口号
    osa_char_t      user[32];     // 设备登陆用户名
    osa_char_t      passwd[32];   // 设备登陆密码
    osa_char_t      company[32];  // 设备厂商
} ATS_DevInfo;


// 设备
struct _ATS_DEVICE
{
    osa_char_t      name[OSA_NAME_MAX];     // 设备名字
    ATS_DevInfo     info;                   // 设备其他信息

    ATS_TestDrv     *drv;                   // 测试驱动，每款设备对应一个测试驱动
    osa_list_t      list;                   // 设备链表

    osa_err_t       (*remove)(ATS_Device *self);    // 移除设备
};


ATS_Device  *ATS_DeviceNew(const osa_char_t *devname);
void        ATS_DeviceDelete(ATS_Device *dev);

void        ATS_DeviceSetInfo(ATS_Device *dev, osa_char_t *ip, osa_uint32_t port, osa_char_t *user, osa_char_t *passwd);

void        ATS_DeviceTest(ATS_Device *dev);


#endif
