/*
 * test_data.h
 *
 * Copyright (C) TuoAn
 *
 */


#ifndef TEST_DATA_H_
#define TEST_DATA_H_

#include "osa.h"

// 测试输入数据
#define     TEST_DATA_IN
// 测试期望输出
#define     TEST_EXPECT_OUT
// 测试实际输出
#define     TEST_REAL_OUT


#define     PTZ_NODE_NAME       "ptz"
#define     NETWORK_NODE_NAME   "network"



typedef struct
{
    /** 输入数据 */
    TEST_DATA_IN    osa_uint32_t    locIn;

    /** 期望输出 */
    TEST_EXPECT_OUT osa_uint32_t    locExpOut;

    /** 实际输出 */
    TEST_REAL_OUT   osa_uint32_t    locRealOut;
} TEST_Ptz;


typedef struct
{

} TEST_Network;


typedef struct
{
} TEST_Sharpness;


typedef struct
{
    TEST_DATA_IN    char    dummyIn[10];
    TEST_EXPECT_OUT char    dummyExpOut[10];
    TEST_REAL_OUT   osa_uint32_t    dummyRealOut;
} TEST_Dummy;




#endif