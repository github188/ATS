/**
 *  report.h
 *
 */

#ifndef __REPORT_H__
#define __REPORT_H__

#include "__class.h"
#include "osa.h"


struct ATS_REPORT_CLASS
{
    osa_uint32_t fd;
    void         *user_data;

    osa_err_t   (*open)(ats_report_t *self, void *user_data);
    osa_err_t   (*close)(ats_report_t *self);
    osa_size_t  (*write)(ats_report_t *self, const osa_char_t *buf, osa_size_t size);
    osa_size_t  (*read)(ats_report_t *self, osa_char_t *outBuf, osa_size_t size);
    osa_err_t   (*ctrl)(ats_report_t *self, osa_uint32_t cmd, void *arg);
};


osa_err_t   ats_report_mod_init();
void        ats_report_mod_exit();

void        ats_report_init(ats_report_t *report);


#endif
