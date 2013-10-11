/**
 *  test_drv.h
 *
 */


#ifndef __TEST_DRV_H__
#define __TEST_DRV_H__


#include "osa.h"
#include "class.h"


#ifdef __cplusplus
extern "C" {
#endif


struct ATS_TEST_DRIVER_CLASS
{
    osa_char_t      name[OSA_NAME_MAX];
    
    osa_char_t      drv_file[OSA_NAME_MAX]; 
    
    osa_list_t      list;
    osa_list_t      tevent_list_head;    

    osa_err_t       (*remove)(ats_tdrv_t *self);  
};


ats_tdrv_t  *ats_tdrv_new(const osa_char_t *name, const osa_char_t *drv_file);
void        ats_tdrv_delete(ats_tdrv_t *tdrv);


ats_tdrv_t  *ats_tdrv_find(ats_bus_t *drv_bus, const osa_char_t *tdrv_name);
osa_err_t   ats_tdrv_register(ats_bus_t *drv_bus, ats_tdrv_t *tdrv);
osa_err_t   ats_tdrv_unregister(ats_bus_t *drv_bus, const osa_char_t *tdrv_name);

// 解析测试驱动文件
osa_err_t   ats_tdrv_parse_drvfile(ats_tdrv_t *drv);

void        ats_tdrv_do_test(ats_tdrv_t *drv);


#ifdef __cplusplus
}
#endif

#endif
