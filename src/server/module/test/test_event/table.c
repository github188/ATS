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


extern ats_tevent_t    dummy_test_event;
extern ats_tevent_t    version_test_event;


static ats_tevent_t   *g_tpTable[] =
{
    TEST_EVENT(dummy_test_event),
    TEST_EVENT(version_test_event),
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
