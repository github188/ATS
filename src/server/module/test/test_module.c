/*
 * test.c
 *
 * Copyright (C) TuoAn
 *
 */

#include "osa.h"
#include "module.h"
#include "conf_xml.h"
#include "log.h"
#include "test.h"
#include "test_event.h"
#include "config.h"


static ats_module_t     test_module;
static ats_mops_t       test_mops;

osa_err_t ats_test_mod_init()
{
    test_mops.begin = test_begin;
    test_mops = test_end;
    
    return ats_module_register(&test_module, "test", &test_mops);
}

void ats_test_mod_exit()
{
    ats_module_unregister("test");
}

