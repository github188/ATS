/**
 *  sys_business.h
 *
 */


#ifndef __SYS_BUSINESS_H__
#define __SYS_BUSINESS_H__


#include "osa.h"


osa_err_t   sysLogin(osa_ioch_t *ioch, osa_msg_t *msg);
osa_err_t   sysExit(osa_ioch_t *ioch, osa_msg_t *msg);
osa_err_t   sysGetDevs(osa_ioch_t *ioch, osa_msg_t *msg);
osa_err_t   sysTestDevice(osa_ioch_t *ioch, osa_msg_t *msg);
osa_err_t   sysLoginDevice(osa_ioch_t *ioch, osa_msg_t *msg);


#endif
