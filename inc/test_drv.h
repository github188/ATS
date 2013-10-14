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
    ats_device_t    *dev;
    osa_char_t      drv_file[OSA_NAME_MAX];

    osa_list_t      list;
    osa_list_t      tevent_list_head;

    osa_err_t       (*remove)(ats_tdrv_t *self);
};


ats_tdrv_t  *ats_tdrv_new(const osa_char_t *drv_file);
void        ats_tdrv_delete(ats_tdrv_t *tdrv);


ats_tdrv_t  *ats_tdrv_load(const osa_char_t *drv_file);
void        ats_tdrv_unload(ats_tdrv_t *drv);

void        ats_tdrv_do_test(ats_tdrv_t *drv);


#ifdef __cplusplus
}
#endif

#endif
