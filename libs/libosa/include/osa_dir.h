/**
 *  osa_dir_t.h
 *
 */


#ifndef __OSA_DIR_H__
#define __OSA_DIR_H__


#include "osa_types.h"
#include "osa_error.h"
#include "osa_config.h"


#ifdef __cplusplus
extern "C"
{
#endif


typedef struct _OSA_DIR
{
    osa_char_t        name[OSA_NAME_MAX];
} osa_dir_t;


typedef struct _OSA_DIR_ENTRY
{
    osa_char_t        name[OSA_NAME_MAX];
} osa_dirent_t;


OSA_API osa_dir_t   *osa_dir_open(const osa_char_t *name);
OSA_API osa_err_t   osa_dir_close(osa_dir_t *dir);
OSA_API osa_err_t   osa_dir_read(osa_dir_t *dir, osa_dirent_t *out_entry);
OSA_API osa_bool_t  osa_dir_is_exist(const osa_char_t *name);


#ifdef __cplusplus
}
#endif

#endif
