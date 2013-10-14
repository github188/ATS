/*
 * cat_main.c
 *
 * Copyright (C) TuoAn
 *
 */


#include "osa.h"
#include "core.h"
#include "data.h"
#include "config.h"
#include "test_event.h"
#include "module/test.h"
#include "module/report.h"
#include "module/erp.h"
#include "module/sys.h"
#include "module/dev_prober.h"


static void __init();
static void __exit();


int main(int argc, char **argv)
{
    
    __init();
  
    do
    {
        if (system_bus_init() != OSA_ERR_OK)
        {
            ats_log_error("Failed to initialize system bus!\n");
            break;
        }

        if (ats_test_mod_init() != OSA_ERR_OK)
        {
            ats_log_error("Failed to initialize <TEST> module!\n");
            break;
        }

        if (ats_report_mod_init() != OSA_ERR_OK)
        {
            ats_log_error("Failed to initialize <REPORT> module!\n");
            break;
        }

        if (ats_erp_mod_init() != OSA_ERR_OK)
        {
            ats_log_error("Failed to initialize <ERP> module!\n");
            break;
        }

        if (ats_devpb_mod_init() != OSA_ERR_OK)
        {
            ats_log_error("Failed to initialize <DEV_PROBER> module!\n");
            break;
        }

        if (ats_sys_mod_init() != OSA_ERR_OK)
        {
            ats_log_error("Failed to initialize <SYS> module!\n");
            break;
        }

        ats_module_all_init(argc, argv);
        
        ats_sys_exec();
    }while (0);
    
    ats_module_all_fini();
    
    system_bus_fini();
    
    __exit();

    return  -1;
}


void __init()
{
    cf_log_t    logcf;
    if (xml_parse_log_conf(ATS_CONFIG_FILE, &logcf) != OSA_ERR_OK)
    {
        osa_log_error("Failed to parse log configuration file!\n");
        return -1;
    }
    
    if (ats_log_open(logcf.logfile) != OSA_ERR_OK)
    {
        osa_log_error("Failed to open log!\n");
        return -1;
    }
}

static void __exit()
{
    ats_log_close();
}