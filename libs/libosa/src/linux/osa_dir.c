/**
 *  osa_dir_t.c
 *
 */


#include "osa_types.h"
#include "osa_dir.h"
#include "osa_macro.h"
#include "osa_error.h"
#include "osa_log.h"
#include "osa_mem.h"
#include "osa_string.h"

#include <dirent.h>


typedef struct
{
    osa_dir_t       parent;
    DIR             *dir;
} LINUX_Dir;


osa_dir_t     *osa_dir_open(const osa_char_t *name)
{
    osa_assert(name != NULL);

    LINUX_Dir   *p = osa_mem_alloc(sizeof(LINUX_Dir));

    p->dir = opendir(name);

    if (OSA_NULL == p->dir)
    {
        osa_log_error("failed to open directory : %s\n", name);

        return NULL;
    }

    strncpy(p->parent.name, name, OSA_NAME_MAX-1);

    return &(p->parent);
}


osa_err_t     osa_dir_close(osa_dir_t *dir)
{
    LINUX_Dir   *p = OSA_STRUCT_ENTRY(dir, LINUX_Dir, parent);

    return closedir(p->dir);
}


osa_err_t     osa_dir_read(osa_dir_t *dir, osa_dirent_t *out_entry)
{
    LINUX_Dir   *p = OSA_STRUCT_ENTRY(dir, LINUX_Dir, parent);

    struct dirent *de = readdir(p->dir);

    if (!de)
    {
        return OSA_ERR_ERR;
    }

    switch (de->d_type)
    {
    case DT_DIR:
    {
        out_entry->ft = OSA_FT_DIRECTORY;
        break;
    }
    case DT_BLK:
    case DT_CHR:
    {
        out_entry->ft = OSA_FT_DEVICE;
        break;
    }
    case DT_REG:
    {
        out_entry->ft = OSA_FT_ARCHIVE;
        break;
    }
    default:
    {
        out_entry->ft = OSA_FT_UNKNOWN;
        break;
    }
    }
    strcpy(out_entry->name, de->d_name);

    return OSA_ERR_OK;
}


osa_bool_t    osa_dir_is_exist(const osa_char_t *name)
{
    osa_assert(name != NULL);

    if (access(name, 0) < 0)
    {
        return OSA_FALSE;
    }

    return OSA_TRUE;
}

void   osa_dir_getcwd(osa_char_t *out_buf, osa_size_t len)
{
    getcwd(out_buf, len);
}

osa_err_t   osa_dir_chdir(const osa_char_t *dpath)
{
    if (chdir(dpath) != 0)
    {
        return OSA_ERR_ERR;
    }
    return OSA_ERR_OK;
}