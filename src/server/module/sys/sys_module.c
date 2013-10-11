/**
 *  sys_module.c
 *
 */

#include "osa.h"
#include "module.h"
#include "conf_xml.h"
#include "log.h"
#include "sys.h"


osa_err_t   sys_begin(ats_module_t *m, int argc, char **argv);
void        sys_end(ats_module_t *m);

static ats_module_t     sys_module;
static ats_mops_t       sys_mops;


osa_err_t ats_sys_mod_init()
{
    sys_mops.begin = sys_begin;
    sys_mops.end = sys_end;
    
    return ats_module_register(&sys_module, "sys", &sys_mops);
}

void ats_sys_mod_exit()
{
    ats_module_unregister("sys");
}


osa_err_t   sys_begin(ats_module_t *m, int argc, char **argv)
{
    
}

void        sys_end(ats_module_t *m)
{
}
