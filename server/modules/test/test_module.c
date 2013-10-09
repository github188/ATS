/*
 * test.c
 *
 * Copyright (C) TuoAn
 *
 */

#include "osa.h"
#include "module.h"
#include "ats.h"
#include "conf_xml.h"
#include "log.h"
#include "test.h"
#include "test_event.h"


static osa_err_t   testConfRead(ATS_Conf *cf, void *out_data);
static osa_err_t   testConfWrite(ATS_Conf *cf, void *data);
static osa_err_t   testModuleEntry(ATS_Conf *cf, int argc, char **argv);
static void        testModuleExit(ATS_Conf *cf);


static ATS_Module  testModule =
{
    .name   = "test",
    .state  = ATS_MODULE_ON,
    .cfops     =
    {
        .open   = NULL,
        .close  = NULL,
        .read   = testConfRead,
        .write  = testConfWrite,
        .ctrl   = NULL,
    },
    .entry  = testModuleEntry,
    .exit   = testModuleExit,
};



osa_err_t   ATS_TestModuleInit(ATS_Conf *cf)
{
    testModule.cf = cf;
    ATS_ModuleRegister(&testModule);

    return OSA_ERR_OK;
}

void    ATS_TestModuleExit()
{
    ATS_ModuleUnregister(&testModule);
}


#ifdef __OSA_OS_WIN32__
#define TEST_POINT_PLUGIN	"C:\\ats\\lib\\libtp.dll"
#endif

#ifdef __OSA_OS_LINUX__
#define TEST_POINT_PLUGIN   "/usr/lib/ats/libtp.so"
#endif

static osa_dll_t   dll;

osa_err_t   ATS_TestLoadPlugin()
{
    if (osa_file_is_exist(TEST_POINT_PLUGIN) != OSA_TRUE)
    {
        ATS_LogError("File not exist : %s\n", TEST_POINT_PLUGIN);
        return OSA_ERR_ERR;
    }

    if (osa_dll_load(&dll, TEST_POINT_PLUGIN) != OSA_ERR_OK)
    {
        ATS_LogError("Failed to load %s!\n", TEST_POINT_PLUGIN);
        return OSA_ERR_ERR;
    }

    return OSA_ERR_OK;
}


ATS_TestEvent   *ATS_TestEventFind(const osa_char_t *name)
{
    typedef void *(*beginItr)();
    typedef void *(*endItr)();
    typedef void *(*nextItr)(void *curr);
    typedef void ** iterator;

    beginItr    begin;
    endItr      end;
    nextItr     next;
    void *entry = NULL;

    if ((entry = osa_dll_sym(&dll, "tableGetBegin")) == NULL)
    {
        ATS_LogError("Can not found tableGetBegin in file %s!\n", TEST_POINT_PLUGIN);
        return OSA_ERR_ERR;
    }
    begin = (beginItr)entry;

    if ((entry = osa_dll_sym(&dll, "tableGetEnd")) == NULL)
    {
        ATS_LogError("Can not found tableGetEnd in file %s!\n", TEST_POINT_PLUGIN);
        return OSA_ERR_ERR;
    }
    end = (endItr)entry;

    if ((entry = osa_dll_sym(&dll, "tableGetNext")) == NULL)
    {
        ATS_LogError("Can not found tableGetNext in file %s!\n", TEST_POINT_PLUGIN);
        return OSA_ERR_ERR;
    }
    next = (nextItr)entry;

    iterator    itr = NULL;
    ATS_TestEvent *node = NULL;

    for (itr = begin(); itr != end(); itr = next(itr))
    {
        node = ( ATS_TestEvent *)*itr;
        if (!strcmp(node->name, name))
        {
            return node;
        }
    }

    return NULL;
}

static osa_err_t   testConfRead(ATS_Conf *cf, void *out_data)
{
    XML_TestModuleRead(cf, out_data);
    return OSA_ERR_OK;
}

static osa_err_t   testConfWrite(ATS_Conf *cf, void *data)
{

}

static osa_err_t   testModuleEntry(ATS_Conf *cf, int argc, char **argv)
{
    CONF_Test   testConf;

    ATS_ConfSetModuleConf(cf, &testModule);
    ATS_ConfRead(cf, &testConf);

    // 如果模块为关闭状态，则不处理
    if (testConf.state == ATS_MODULE_OFF)
    {
        return OSA_ERR_OK;
    }
    else
    {
        return OSA_ERR_OK;
    }
}

static void    testModuleExit(ATS_Conf *cf)
{

}
