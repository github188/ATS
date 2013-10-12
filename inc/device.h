/**
 *  device.h
 *
 */


#ifndef __DEVICE_H__
#define __DEVICE_H__


#include "osa.h"
#include "class.h"


typedef struct _ATS_DEVICE_INFO
{
    osa_char_t      ip[20];       // 设备的IP地址
    osa_uint32_t    port;         // 设备的端口号
    osa_char_t      user[32];     // 设备登陆用户名
    osa_char_t      passwd[32];   // 设备登陆密码
    osa_char_t      company[32];  // 设备厂商
} ats_devinfo_t;



struct ATS_DEVICE_CLASS
{
    osa_char_t      name[OSA_NAME_MAX];     // 设备名字
    ats_devinfo_t   info;                   // 设备其他信息

    ats_tdrv_t      *drv;                   // 测试驱动，每款设备对应一个测试驱动
    ats_sdk_t       *sdk;                   // SDK
    osa_list_t      list;                   // 设备链表

    osa_err_t       (*remove)(ats_device_t *self);    // 移除设备
};


ats_device_t    *ats_device_new(const osa_char_t *dev_name);
void            ats_device_delete(ats_device_t *dev);

void            ats_device_setinfo(ats_device_t *dev, 
                                const osa_char_t *ip, osa_uint32_t port, 
                                const osa_char_t *user, const osa_char_t *passwd);

ats_device_t    *ats_device_find(ats_bus_t *dev_bus, const osa_char_t *dev_name);
osa_err_t       ats_device_register(ats_bus_t *dev_bus, ats_device_t *dev);
osa_err_t       ats_device_unregister(ats_bus_t *dev_bus, const osa_char_t *dev_name);


#endif
