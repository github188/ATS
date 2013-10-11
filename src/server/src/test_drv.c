/**
 *  test_drv.c
 *
 */


#include "osa.h"
#include "test_drv.h"
#include "__class.h"
#include "report.h"
#include "conf_xml.h"
#include "log.h"


static osa_err_t    _def_init(ats_tevent_t *tevent);
static ats_result_t _def_start_test(void *testCase);
static void         _def_suss_cb(ats_tevent_t *tevent);
static void         _def_fail_cb(ats_tevent_t *tevent);
static void         _def_fini(ats_tevent_t *tevent);
static osa_err_t    _def_trv_remove(ats_tdrv_t *tevent);


ats_tdrv_t  *ats_tdrv_new(const osa_char_t *name, const osa_char_t *drv_file)
{
    ats_tdrv_t *drv = (ats_tdrv_t *)osa_mem_alloc(sizeof(ats_tdrv_t));

    strncpy(drv->name, name, OSA_NAME_MAX - 1);
    strncpy(drv->drv_file, drv_file, OSA_NAME_MAX - 1);
    osa_list_init(&drv->list);
    osa_list_init(&drv->tevent_list_head);
    
    drv->remove = _def_trv_remove;
    
    return drv;
}


void    ats_tdrv_delete(ats_tdrv_t *tdrv)
{
    if (!tdrv)
    {
        return;
    }
    
    ats_tevent_t    *node = NULL;
    osa_list_t      *l = NULL;

    for (l = tdv->tevent_list_head.next; l != &tdv->tevent_list_head; l = l->next)
    {
        node = osa_list_entry(l, ats_tevent_t, list);
        if (node->ops && node->ops->test_stop)
        {
            node->ops->test_stop(node);
        }
        if (node->ops && node->ops->end)
        {
            node->ops->end(node);
        }
    }
    
    osa_list_remove(&tdv->tevent_list_head);
    osa_mem_free(tdv);
}


ats_tdrv_t  *ats_tdrv_find(ats_bus_t *drv_bus, const osa_char_t *tdrv_name)
{
    osa_assert(tdrv_name != NULL);

    ats_tdrv_t  *node = NULL;
    osa_list_t  *l = NULL;

    for (l = drv_bus->ele_list_head.next; l != &drv_bus->ele_list_head; l = l->next)
    {
        node = osa_list_entry(l, ats_tdrv_t, list);
        if (!strcmp(node->name, tdrv_name))
        {
            return node;
        }
    }

    return NULL;
}


osa_err_t ats_tdrv_register(ats_bus_t *drv_bus, ats_tdrv_t *tdrv);
{
    ats_device_t *p = NULL
    
    if ((p = ats_tdrv_find(drv_bus, tdrv->name)) != NULL)
    {
        ats_log_warn("Replace Device : name(%s)\n", tdrv->name);
        p = tdrv;
    }
    else
    {
        ats_log_info("Register new device : name(%s)\n", tdrv->name);
        osa_list_insert_before(&dev_bus->ele_list_head, &tdrv->list);
    }
    
    return OSA_ERR_OK;
}


osa_err_t ats_tdrv_unregister(ats_bus_t *drv_bus, const osa_char_t *tdrv_name)
{
    osa_assert(tdrv_name != NULL);
    
    ats_device_t *p = NULL;
    
    if ((p = ats_device_find(drv_bus, tdrv_name)) != NULL)
    {
        osa_list_remove(&p->list);
        if (p->remove)
        {
            p->remove();
        }
        ats_log_info("Unregister test driver : name(%s)\n", p->name);
    }
    
    return OSA_ERR_OK;
}


void ats_tdrv_do_test(ats_tdrv_t *drv)
{
    ats_tevent_t   *node = NULL;
    
    /** attention: char pointer */
    osa_uint8_t     *ptr = NULL;

    osa_list_t  *l = NULL;
    osa_uint32_t    i;
    
    for (l = drv->tevent_list_head.next; l != &drv->tevent_list_head; l = l->next)
    {
        node = osa_list_entry(l, ats_tevent_t, list);

        if (!node->init)
            node->init = _def_init;
        if (!node->test_start)
            node->test_start = _def_start_test;
        if (!node->test_stop)
            node->test_stop = _def_stop_test;
        if (!node->suss_cb)
            node->suss_cb = _def_suss_cb;
        if (!node->fail_cb)
            node->fail_cb = _def_fail_cb;
        if (!node->fini)
            node->fini = _def_fini;

        if (node->begin(node) != OSA_ERR_OK)
        {
            ats_log_error("Failed to begin test!\n");
            continue;
        }
        
        node->attr.stat.fail_times = 0;
        
        for (i = 0; i < node->attr.tcb.tc_num; i++)
        {
            ats_log_info("Test case : %d\n", i + 1);

            // 获取每一组测试用例数据的首地址
            ptr = node->testCaseBox.privData + i * node->testCaseBox.caseSize;

            node->result = node->test_start((void *)ptr);

            if (node->result == ATS_SUCCEED)
            {
                node->suss_cb(node);
            }
            else if (node->result == ATS_FAILED)
            {
                node->fail_cb(node);
                node->attr.stat.fail_times ++;
            }
        }
        
        node->attr.stat.test_times = node->attr.tcb.tc_num;
        
        node->fini(node);
    }
}


osa_err_t ats_tdrv_parse_drvfile(ats_tdrv_t *drv)
{
    return xml_parse_tdrvfile(drv);
}


static osa_err_t _def_init(ats_tevent_t *tevent)
{
    return OSA_ERR_OK;
}

static ats_result_t  _def_start_test(void *testCase)
{
    return ATS_TEST_SUCCESS;
}

static void _def_suss_cb(ats_tevent_t *tevent)
{
}

static void _def_fail_cb(ats_tevent_t *tevent)
{
}

static void _def_fini(ats_tevent_t *tevent)
{
    char buf[1024] = {0};

    int testTimes = tevent->attr.stat.test_times;
    int failTimes = tevent->attr.stat.fail_times;
    sprintf(buf, "[%s] Test times : %d, Failed times : %d, Fail rate : %.2f%%", tevent->name, testTimes, failTimes, failTimes / (testTimes * 1.0) * 100);
    tevent->report->write(tevent->report, buf, strlen(buf));
}

static osa_err_t _def_trv_remove(ats_tdrv_t *tevent)
{
    if (tevent)
    {
        osa_list_remove(&tevent->list);
        ats_tdrv_delete(tevent);
    }
}
