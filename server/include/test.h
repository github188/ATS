/**
 *  test.h
 *
 */


#ifndef __TEST_H__
#define __TEST_H__

#include "osa.h"


osa_err_t       ATS_TestModuleInit(ATS_Conf *cf);
void            ATS_TestModuleExit();

// 加载测试点插件
osa_err_t       ATS_TestLoadPlugin();


#endif