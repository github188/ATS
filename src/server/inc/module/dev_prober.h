/**
 *  dev_prober.h
 *
 */

#ifndef __DEV_PROBER_H__
#define __DEV_PROBER_H__


#include "osa.h"
#include "core.h"
#include "__class.h"


#ifdef __cplusplus
extern "C"
{
#endif


struct ATS_DEV_PROBER_CLASS
{
    osa_char_t  *name;          // 名字
    osa_char_t  *dev_support;   // 支持的设备表,以逗号分隔
    osa_bool_t  (*dev_is_ok)(ats_devinfo_t *devinfo);     // 设备是否OK
};

osa_err_t   ats_devpb_mod_init();
void        ats_devpb_mod_exit();

osa_err_t   ats_devpb_init();

osa_bool_t  ats_devpb_is_support(ats_devpb_t        *dp,
                                 const osa_char_t   *dev_name);
void        ats_devpb_probe();

// table
extern ats_devpb_t      *g_dptable[];
// table size
extern osa_uint32_t     g_dpnum;

// 获取设备对应的设备检测器
ats_devpb_t *ats_devpb_obtain(const osa_char_t *dev_name);

#ifdef __cplusplus
}
#endif

#endif
