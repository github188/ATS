/**
 *  dev_prober.h
 *
 */

#ifndef __DEV_PROBER_H__
#define __DEV_PROBER_H__


#include "__class.h"
#include "osa.h"


#ifdef __cplusplus
extern "C"
{
#endif


struct ATS_DEV_PROBER_CLASS
{
    osa_char_t  name[OSA_NAME_MAX];

    void        (*probe)();     // 探测设备
};



osa_err_t   ats_devprober_mod_init();
void        ats_devprober_mod_exit();


#ifdef __cplusplus
}
#endif

#endif
