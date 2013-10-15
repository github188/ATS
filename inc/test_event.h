/**
* test_event.h
*
*/

#ifndef __TEST_EVENT_H__
#define __TEST_EVENT_H__


#include "osa.h"
#include "class.h"


#ifdef __cplusplus
extern "C" {
#endif

/** test result */
typedef enum
{
    ATS_SUCCEED     = 0,
    ATS_FAILED      = -1,
}
ats_result_t;


/** test case box */
typedef struct
{
    osa_uint32_t    tc_num;     // 测试用例数量
    osa_uint32_t    tc_size;    // 每个测试用例大小
    void           *tc_cases;     // 测试用例数据地址
} ats_tcasebox_t;


/** test statistic */
typedef struct
{
    osa_uint32_t    test_times;     // 总共测试次数
    osa_uint32_t    fail_times;     // 失败次数
} ats_tstatistic_t;


/** test attribute */
typedef struct
{
    osa_uint32_t        proi;   // 测试优先级，数字越小优先级越大
    ats_tcasebox_t      tcb;    // 测试用例容器
    ats_result_t        result; // 测试结果
    ats_tstatistic_t    stat;  // 结果统计
} ats_testattr_t;


/** test ops */
typedef struct
{
    /** begin function */
    osa_err_t       (*init)(ats_tevent_t *tevent);
    /** test start function */
    ats_result_t    (*test_start)(void *testCase);
    /** test stop function */
    void            (*test_stop)(ats_tevent_t *tevent);
    /** success callback function */
    void            (*suss_cb)(ats_tevent_t *tevent);
    /** fail callback function */
    void            (*fail_cb)(ats_tevent_t *tevent);
    /** end function */
    void            (*fini)(ats_tevent_t *tevent);
} ats_tevent_ops_t;


struct ATS_TEST_EVENT_CLASS
{
    osa_char_t      *name;      // 测试项名称
    ats_tevent_ops_t ops;       // ops

    /** private data */
    ats_testattr_t  attr;       // attribute
    void	        *report;    // report
    osa_list_t      list;       // 链表
};


// 加载测试项插件
osa_err_t       ats_tevent_plugin_load(const osa_char_t *plugin_file);
void            ats_tevent_plugin_unload();

ats_tevent_t    *ats_tevent_get(const osa_char_t *tevent_name);

ats_tevent_t    *ats_tevent_find(ats_tdrv_t *drv, const osa_char_t *tevent_name);
osa_err_t       ats_tevent_register(ats_tdrv_t *drv, ats_tevent_t *tevent);
osa_err_t       ats_tevent_unregister(ats_tdrv_t *drv, const osa_char_t *tevent_name);


#ifdef __cplusplus
}
#endif

#endif /* ATS_TEST_H_ */
