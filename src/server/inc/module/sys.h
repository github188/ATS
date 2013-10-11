/**
 *  sys.h
 *
 */


#ifndef __SYS_H__
#define __SYS_H__

#include "osa.h"


osa_err_t   ats_sys_mod_init();
void        ats_sys_mod_exit();

void        ats_system_init();
void        ats_system_exec();

#endif
