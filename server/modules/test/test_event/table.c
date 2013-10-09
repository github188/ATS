/*
 * test_api.h
 *
 * Copyright (C) TuoAn
 *
 */


#include "osa.h"
#include "test_event.h"



/**----------------------------------------*/
#define TEST_EVENT(tp)  &tp


extern ATS_TestEvent    dummyTestEvent;
extern ATS_TestEvent    versionTestEvent;


static ATS_TestEvent   *g_tpTable[] =
{
    TEST_EVENT(dummyTestEvent),
    TEST_EVENT(versionTestEvent),
};



/**----------------------------------------*/
void   *tableGetBegin()
{
    return (void *)&g_tpTable[0];
}

void   *tableGetEnd()
{
    int end = (sizeof(g_tpTable)/sizeof(g_tpTable[0]));
    return (void *)&g_tpTable[end];
}

void   *tableGetNext(void *curr)
{
    void *next = curr + sizeof(g_tpTable[0]);
    return next;
}
