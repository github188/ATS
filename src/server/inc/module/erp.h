/**
 * erp.h
 *
 */

#ifndef __ERP_H__
#define __ERP_H__


#include "osa.h"
#include "__class.h"


struct ATS_ERP_CLASS
{
    osa_err_t       (*init)();
    void            (*exit)();
    void            *(*connect)(const char *erpFile, osa_uint32_t timeout);
    osa_uint8_t     (*disconnect)(void *erpFd);
    osa_err_t       (*send)(void *erpFd, void *data, osa_size_t size);

};


osa_err_t   ats_erp_mod_init();
void        ats_erp_mod_exit();


#endif /* ATS_ERP_H_ */
