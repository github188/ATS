/*
 * erp.c
 *
 * Copyright (C) TuoAn
 *
 */

#include "osa.h"
#include "module.h"
#include "conf_xml.h"
#include "log.h"
#include "data.h"
#include "module/erp.h"


static osa_err_t   erp_begin(ats_module_t *m, int argc, char **argv);
static void        erp_end(ats_module *m);


static ats_module_t erp_module;
static ats_mops_t   erp_mops;


osa_err_t ats_erp_mod_init()
{
    erp_mops.begin = erp_begin;
    erp_ops.end = erp_end;
    
    return ats_module_register(&erp_module, "erp", &erp_mops);
}

void ats_erp_mod_exit()
{
    ats_moudle_unregister("erp");
}


static osa_err_t erp_begin(ats_module_t *m, int argc, char **argv)
{
    cf_erp_t erpcf;
    
    if (xml_parse_erp_conf(m->conf_file, &erpcf) != OSA_ERR_OK)
    {
        ats_log_error("Failed to parse erp configuration file!\n");
        return OSA_ERR_ERR;
    }
    
    return OSA_ERR_OK;
}

static void erp_end(ats_module *m)
{
    
}
