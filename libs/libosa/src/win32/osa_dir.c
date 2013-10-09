/**
 *  osa_dir_t.c
 *
 */


#include "osa_types.h"
#include "osa_dir.h"
#include "osa_error.h"
#include "osa_log.h"
#include "osa_macro.h"
#include "osa_mem.h"
#include "osa_cvt.h"


#include <io.h>


typedef struct _WIN32_DIR
{
    osa_dir_t           parent;
    HANDLE              dir;
    WIN32_FIND_DATA     finddata;
} WIN32_Dir;



osa_dir_t   *osa_dir_open(const osa_char_t *name)
{
    osa_assert(name != NULL);

    WIN32_Dir   *p = (WIN32_Dir *)osa_mem_alloc(sizeof(WIN32_Dir));

    p->dir = FindFirstFile((LPCSTR)name, &p->finddata );

    if (p->dir == INVALID_HANDLE_VALUE)
    {
        goto err;
    }

    strncpy(p->parent.name, name, OSA_NAME_MAX-1);

    return &(p->parent);

err:
    osa_log_error("failed to open directory : %s, %d\n", name, GetLastError());
    osa_mem_free(p);
    return NULL;
}


osa_err_t     osa_dir_close(osa_dir_t *dir)
{
    WIN32_Dir   *p = OSA_STRUCT_ENTRY(dir, WIN32_Dir, parent);

    osa_mem_free(p);

    return OSA_ERR_OK;
}


osa_err_t     osa_dir_read(osa_dir_t *dir, osa_dirent_t *out_entry)
{
    WIN32_Dir   *p = OSA_STRUCT_ENTRY(dir, WIN32_Dir, parent);

    WIN32_FIND_DATA finddata;

    if (!FindNextFile(p->dir, &finddata))
    {
        printf("---------%d\n", GetLastError());
        return OSA_ERR_ERR;
    }

    // BUG: ignore current directory

    strncpy(out_entry->name, (char *)finddata.cFileName, OSA_NAME_MAX-1);

    return OSA_ERR_OK;
}


osa_bool_t    osa_dir_is_exist(const osa_char_t *name)
{
    osa_assert(name != NULL);

    if (_access(name, 0) < 0)
    {
        return OSA_FALSE;
    }

    return OSA_TRUE;
}
