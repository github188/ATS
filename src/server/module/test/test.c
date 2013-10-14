/**
 *  test.c
 *
 */
 
 
#include "osa.h"
#include "log.h"

#include "module/test.h"


void ats_test_device_test(ats_device_t *dev)
{
    if (dev->drv)
    {
        ats_log_info("Start test device : %s\n", dev->name);
        
        ats_tdrv_do_test(dev->drv);
    }
}