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
    intptr_t            handler;
    struct _finddata_t  finddata;
} WIN32_Dir;



osa_dir_t   *osa_dir_open(const osa_char_t *name)
{
    osa_assert(name != NULL);

    if (osa_dir_is_exist(name) != OSA_TRUE)
    {
        osa_log_error("Directory not exist : %s\n", name);
        return NULL;
    }

    osa_char_t file[MAX_PATH+1] = {0};

    strncpy(file, name, strlen(name));
    strcat(file, "\\*.*");

    WIN32_Dir   *p = (WIN32_Dir *)osa_mem_alloc(sizeof(WIN32_Dir));

    p->handler = _findfirst(file, &p->finddata );

    if (p->handler < 0)
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

    _findclose(p->handler);

    osa_mem_free(p);

    return OSA_ERR_OK;
}


osa_err_t     osa_dir_read(osa_dir_t *dir, osa_dirent_t *out_entry)
{
    WIN32_Dir   *p = OSA_STRUCT_ENTRY(dir, WIN32_Dir, parent);

    if (_findnext(p->handler, &p->finddata) != 0)
    {
        return OSA_ERR_ERR;
    }

    int attr = p->finddata.attrib;

    if (attr & _A_ARCH)
    {
        out_entry->ft = OSA_FT_ARCHIVE;
    }
    else if (attr & _A_SUBDIR)
    {
        out_entry->ft = OSA_FT_DIRECTORY;
    }
    else
    {
        out_entry->ft = OSA_FT_UNKNOWN;
    }

    strncpy(out_entry->name, p->finddata.name, OSA_MIN(FILENAME_MAX, OSA_NAME_MAX-1));
    out_entry->size = p->finddata.size;

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
