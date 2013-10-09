/*
 * cat_test.h
 *
 * Copyright (C) TuoAn
 *
 */

#include "osa.h"
#include "test_event.h"
#include "log.h"
#include "ats.h"


#ifdef __cplusplus
extern "C" {
#endif


ATS_TestEvent   *ATS_TestEventNew(const char *name)
{
    ATS_TestEvent   *p = (ATS_TestEvent *)malloc(sizeof(ATS_TestEvent));

    if (!p)
    {
        ATS_LogError("No memory !\n");

        return NULL;
    }

    memset(p, 0, sizeof(ATS_TestEvent));

    strncpy(p->name, name, OSA_NAME_MAX-1);

    return p;
}


void    ATS_TestEventDelete(ATS_TestEvent *self)
{
    if (!self)
    {
        return;
    }

    free(self);
}


#ifdef __cplusplus
}
#endif
