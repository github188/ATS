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


typedef enum
{
    OSA_FT_ARCHIVE = 1,         // archive
    OSA_FT_DIRECTORY = 2,       // directory
    OSA_FT_DEVICE = 4,          // device
    OSA_FT_UNKNOWN = 8          // unknown
}osa_ftype_t;


typedef struct _OSA_DIR
{
    osa_char_t        name[OSA_NAME_MAX];
} osa_dir_t;


typedef struct _OSA_DIR_ENTRY
{
    osa_char_t          name[OSA_NAME_MAX];
    osa_ftype_t         ft;
    osa_size_t          size;
} osa_dirent_t;


OSA_API osa_dir_t   *osa_dir_open(const osa_char_t *name);
OSA_API osa_err_t   osa_dir_close(osa_dir_t *dir);
OSA_API osa_err_t   osa_dir_read(osa_dir_t *dir, osa_dirent_t *out_entry);
OSA_API osa_bool_t  osa_dir_is_exist(const osa_char_t *name);
OSA_API void        osa_dir_getcwd(osa_char_t *out_buf, osa_size_t len);
OSA_API osa_err_t   osa_dir_chdir(const osa_char_t *dpath);

#ifdef __cplusplus
}
#endif

#endif
