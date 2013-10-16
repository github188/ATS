/**
 *  report.h
 *
 */

#ifndef __REPORT_H__
#define __REPORT_H__

#include "osa.h"
#include "__class.h"


struct ATS_REPORT_CLASS
{
    osa_uint32_t fd;
    void         *user_data;
};


osa_err_t   ats_report_mod_init();
void        ats_report_mod_exit();


ats_report_t *ats_report_open(void *user_data);
void         ats_report_close(ats_report_t *rpt);
osa_size_t   ats_report_write(ats_report_t      *rpt, 
                              const osa_char_t  *buf, 
                              osa_size_t        size);
osa_size_t   ats_report_read(ats_report_t   *rpt, 
                             osa_char_t     *out_buf, 
                             osa_size_t     size);
osa_err_t    ats_report_ctrl(ats_report_t   *rpt, 
                             osa_uint32_t   cmd, 
                             void           *param);

#endif
