/*
 * erp.c
 *
 * Copyright (C) TuoAn
 *
 */

#include "osa.h"
#include "core.h"
#include "xml.h"
#include "config.h"
#include "module/erp.h"


static osa_err_t   erp_begin(ats_module_t *m, int argc, char **argv);
static void        erp_end(ats_module_t *m);


static ats_module_t erp_module;
static ats_mops_t   erp_mops;


osa_err_t ats_erp_mod_init()
{
    erp_mops.begin = erp_begin;
    erp_mops.end =   erp_end;
    
    erp_module.conf_file = ATS_CONFIG_FILE;
    
    return ats_module_register(&erp_module, "erp", &erp_mops);
}

void ats_erp_mod_exit()
{
    ats_module_unregister("erp");
}


static osa_err_t erp_begin(ats_module_t *m, int argc, char **argv)
{
    return OSA_ERR_OK;
}

static void erp_end(ats_module_t *m)
{
    
}
