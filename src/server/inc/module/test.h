/**
 *  test.h
 *
 */


#ifndef __TEST_H__
#define __TEST_H__


#include "osa.h"
#include "device.h"


osa_err_t   ats_test_mod_init();
void        ats_test_mod_exit();

void        ats_test_device_test(ats_device_t *dev);

#endif
