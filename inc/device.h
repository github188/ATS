/**
 *  device.h
 *
 */


#ifndef __DEVICE_H__
#define __DEVICE_H__


#include "osa.h"
#include "class.h"

#ifdef __cplusplus
extern "C"
{
#endif

typedef enum
{
    DT_NET_CAMERA = 1,      // 网络摄像机
    DT_SIM_CAMERA = 2,      // 模拟球机

    DT_DUMMY
}
ats_devtype_t;

typedef struct _ATS_DEVICE_INFO
{
    union
    {
        osa_char_t  addr[32];
        struct _ipaddr
        {
            osa_char_t  ip[20];
            osa_uint32_t port;
        } net_addr;
        osa_char_t  con_addr[32];
    } addr;
    osa_char_t      user[32];     // 设备登陆用户名
    osa_char_t      passwd[32];   // 设备登陆密码
    osa_char_t      company[32];  // 设备厂商
} ats_devinfo_t;



struct ATS_DEVICE_CLASS
{
    osa_char_t      name[OSA_NAME_MAX];     // 设备名字
    ats_devtype_t   type;                   // 设备类型
    ats_devinfo_t   info;                   // 设备其他信息

    ats_tdrv_t      *drv;                   // 测试驱动，每款设备对应一个测试驱动
    ats_sdk_t       *sdk;                   // SDK
    osa_list_t      list;                   // 设备链表

    void            (*remove)(ats_device_t *self);    // 移除设备
};


ats_device_t    *ats_device_new(const osa_char_t    *dev_name, 
                                ats_devtype_t       type);
void            ats_device_delete(ats_device_t *dev);

void            ats_device_setinfo(ats_device_t     *dev,
                                   const osa_char_t *addr,
                                   const osa_char_t *user, 
                                   const osa_char_t *passwd);
                                   
osa_err_t       ats_device_load_tdrv(ats_device_t       *dev, 
                                     const osa_char_t   *tdrv_file);
osa_err_t       ats_device_load_sdk(ats_device_t        *dev, 
                                    const osa_char_t    *sdk_plugin);
void            ats_device_unload_tdrv(ats_device_t *dev);
void            ats_device_unload_sdk(ats_device_t *dev);
                                   
ats_device_t    *ats_device_find(ats_bus_t          *dev_bus, 
                                 const osa_char_t   *dev_name);
osa_err_t       ats_device_register(ats_bus_t       *dev_bus, 
                                    ats_device_t    *dev);
osa_err_t       ats_device_unregister(ats_bus_t         *dev_bus, 
                                      const osa_char_t  *dev_name);

void            ats_device_print(ats_device_t *dev);

#ifdef __cplusplus
}
#endif

#endif
