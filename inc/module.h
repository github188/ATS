/**
 * module.h
 *
 */

#ifndef __MOUDLE_H__
#define __MODULE_H__


#include "osa.h"
#include "class.h"


#ifdef __cplusplus
extern "C" {
#endif


typedef enum
{
    ATS_OFF = 0,
    ATS_ON = 1,
}
ats_switch_t;


typedef struct
{
    osa_err_t   (*begin)(ats_module_t *m, int argc, char **argv);
    void        (*end)(ats_module_t *m);
} ats_mops_t;

struct ATS_MODULE_CLASS
{
    osa_char_t      name[OSA_NAME_MAX];
    osa_char_t      *conf_file;

    ats_switch_t    state;
    osa_list_t      list;

    ats_mops_t      *ops;
    void            *priv_data;     // 模块数据
};


#define ATS_MODULE_MAX      10


ats_module_t    *ats_module_find(const char *mod_name);
osa_err_t       ats_module_register(ats_module_t *m, const osa_char_t *name, ats_mops_t *ops);
osa_err_t       ats_module_unregister(const osa_char_t *mod_name);

void            ats_module_all_init(int argc, char **argv);
void            ats_module_all_fini();


#ifdef __cplusplus
}
#endif

#endif /* MODULE_H_ */
