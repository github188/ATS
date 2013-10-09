/**
 *  bus.h
 *
 */


#ifndef __DEV_BUS_H__
#define __DEV_BUS_H__


#include "ats.h"
#include "osa.h"
#include "test_event.h"
#include "device.h"



#ifdef __cplusplus
extern "C" {
#endif


struct _ATS_DEVICE_BUS
{
    osa_list_t      devListHead;        // 设备列表头节点
    osa_list_t      drvListHead;        // 测试驱动列表头节点

    // 匹配函数，对设备和测试驱动进行匹配
    osa_err_t       (*match)(ATS_Device *dev, ATS_TestDrv *drv);
};


osa_err_t   ATS_DevBusInit();

ATS_DevBus  *ATS_DevBusGet();


// 在总线上找设备
ATS_Device  *ATS_DevBusFindDev(const osa_char_t *dev_name);

// 挂接设备到总线
osa_err_t   ATS_DevBusHangDev(ATS_Device *dev);

// 从总线上卸下设备
osa_err_t   ATS_DevBusUnhangDev(const osa_char_t *dev_name);

// 在总线上找测试驱动
ATS_TestDrv *ATS_DevBusFindDrv(const osa_char_t *drv_name);

// 挂接测试驱动到总线
osa_err_t   ATS_DevBusHangDrv(ATS_TestDrv *drv);

// 卸载测试驱动
osa_err_t   ATS_DevBusUnhangDrv(const osa_char_t *drv_name);

// 移除总线上挂载的所有设备
osa_err_t   ATS_DevBusRemoveAllDev();

// 移除总线上挂载的所有测试驱动
osa_err_t   ATS_DevBusRemoveAllDrv();

#ifdef __cplusplus
}
#endif

#endif
