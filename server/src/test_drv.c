/**
 *  test_drv.c
 *
 */


#include "osa.h"
#include "test_drv.h"
#include "report.h"
#include "conf_xml.h"
#include "log.h"


static osa_err_t       _defParseConf(ATS_TestEvent *self, osa_char_t *cf);
static osa_err_t       _defBegin(ATS_TestEvent *self);
static ATS_TestResult  _defStartTest(void *testCase);
static void            _defSussFunc(ATS_TestEvent *self);
static void            _defFailFunc(ATS_TestEvent *self);
static void            _defEnd(ATS_TestEvent *self);


ATS_TestDrv *ATS_TestDrvNew(const osa_char_t *name, const osa_char_t *cf)
{
    ATS_TestDrv *td = osa_mem_alloc(sizeof(ATS_TestDrv));

    strncpy(td->name, name, OSA_NAME_MAX - 1);
    strncpy(td->cf, cf, OSA_NAME_MAX - 1);

    ATS_ReportSysInit(&td->report);

    osa_list_init(&td->teListHead);

    return td;
}


void ATS_TestDrvDelete(ATS_TestDrv *tdv)
{
    if (tdv)
    {
        osa_list_remove(&tdv->teListHead);
        osa_mem_free(tdv);
    }
}


ATS_TestEvent *ATS_TestDrvFindTestEvent(ATS_TestDrv *tdv, const char *name)
{
    osa_assert(name != NULL);

    ATS_TestEvent   *node = NULL;
    osa_list_t  *l = NULL;

    for (l = tdv->teListHead.next; l != &tdv->teListHead; l = l->next)
    {
        node = osa_list_entry(l, ATS_TestEvent, list);

        // 找到
        if (!strcmp(node->name, name))
        {
            return node;
        }
    }

    return NULL;
}

osa_err_t ATS_TestDrvRegisterTestEvent(ATS_TestDrv *tdv, ATS_TestEvent *tp)
{
    if (!tp)
    {
        return OSA_ERR_ERR;
    }

    ATS_LogInfo("Register TestPoint (%s) to TestDriver(%s)\n", tp->name, tdv->name);

    ATS_TestEvent   *p = NULL;

    if ((p = ATS_TestDrvFindTestEvent(tdv, tp->name)) != NULL)
    {
        ATS_LogWarn("Replace TestPoint: name(%s)\n", tp->name);
        p = tp;
    }
    else
    {
        osa_list_insert_before(tdv->teListHead.next, &tp->list);
    }

    return OSA_ERR_OK;
}


osa_err_t ATS_TestDrvUnregisterTestEvent(ATS_TestDrv *tdv, const char *name)
{
    osa_assert(name != NULL);

    ATS_TestEvent   *p = NULL;

    if ((p = ATS_TestDrvFindTestEvent(tdv, name)) != NULL)
    {
        ATS_LogInfo("Unregister TestPoint (%s) from TestDriver(%s)\n", name, tdv->name);
        osa_list_remove(&p->list);
    }

    return OSA_ERR_OK;
}

osa_err_t ATS_TestDrvLoad(ATS_Conf *cf)
{
    return XML_DevModuleParse(cf);
}


void ATS_TestDrvDoTest(ATS_TestDrv *drv)
{
    ATS_TestEvent   *node = NULL;

    // 测试用例数据指针
    // 此处需要使用指向char数据的指针，char指针每次递增1个字节，不能选择其他类型的指针
    osa_uint8_t     *testCasePtr = NULL;

    osa_list_t  *l = NULL;
    osa_uint32_t    i;
    osa_size_t  failedTimes = 0;

    for (l = drv->teListHead.next; l != &drv->teListHead; l = l->next)
    {
        node = osa_list_entry(l, ATS_TestEvent, list);

        if (!node->parseConf)
            node->parseConf = _defParseConf;
        if (!node->begin)
            node->begin = _defBegin;
        if (!node->startTest)
            node->startTest = _defStartTest;
        if (!node->successFunc)
            node->successFunc = _defSussFunc;
        if (!node->failedFunc)
            node->failedFunc = _defFailFunc;
        if (!node->end)
            node->end = _defEnd;

        node->report = &drv->report;

        if (node->parseConf(node, drv->cf) != OSA_ERR_OK)
        {
            ATS_LogError("Failed to parse config for test : %s\n", node->name);
            continue;
        }

        if (node->begin(node) != OSA_ERR_OK)
        {
            ATS_LogError("Failed to begin test!\n");
            continue;
        }

        for (i = 0; i < node->testCaseBox.caseNum; i++)
        {
            ATS_LogInfo("Test case : %d\n", i + 1);

            // 获取每一组测试用例数据的首地址
            testCasePtr = node->testCaseBox.privData + i * node->testCaseBox.caseSize;

            node->result = node->startTest((void *)testCasePtr);

            if (node->result == ATS_TEST_SUCCESS)
            {
                if (node->successFunc)
                {
                    node->successFunc(node);
                }
            }
            else if (node->result == ATS_TEST_FAILED)
            {
                if (node->failedFunc)
                {
                    node->failedFunc(node);
                }
                failedTimes++;
            }
        }

        // 统计结果
        node->statistic.testTimes = node->testCaseBox.caseNum;
        node->statistic.failedTimes = failedTimes;

        node->end(node);
    }
}


osa_err_t ATS_TestDrvParseConf(ATS_TestDrv *drv)
{
    ATS_LogInfo("Parse configuration file for TestDriver: name(%s), conf_file(%s)\n", drv->name, drv->cf);
    XML_ParseTestDrvFile(drv);
}


static osa_err_t _defParseConf(ATS_TestEvent *self, osa_char_t *cf)
{
    return OSA_ERR_OK;
}

static osa_err_t _defBegin(ATS_TestEvent *self)
{
    return OSA_ERR_OK;
}


static ATS_TestResult  _defStartTest(void *testCase)
{
    return ATS_TEST_SUCCESS;
}


static void _defSussFunc(ATS_TestEvent *self)
{
}


static void _defFailFunc(ATS_TestEvent *self)
{
}


static void    _defEnd(ATS_TestEvent *self)
{
    char buf[1024] = {0};

    int testTimes = self->statistic.testTimes;
    int failTimes = self->statistic.failedTimes;
    sprintf(buf, "[%s] Test times : %d, Failed times : %d, Fail rate : %.2f%%", self->name, testTimes, failTimes, failTimes / (testTimes * 1.0) * 100);
    self->report->write(self->report, buf, strlen(buf));
}
