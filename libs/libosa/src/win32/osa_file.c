/**
 *  osa_file_t.c
 *
 */

#include "osa_types.h"
#include "osa_file.h"
#include "osa_log.h"
#include "osa_error.h"
#include "osa_mem.h"
#include "osa_cvt.h"

#include <io.h>


osa_file_t    *osa_file_open(const osa_char_t *name, osa_char_t *mode)
{
    osa_assert(name != NULL);

    WIN32_FIND_DATA     info;
    HANDLE              h;

    osa_file_t *file = (osa_file_t *)osa_mem_alloc(sizeof(osa_file_t ));

    // for stdin, stdout, stderr, no operation
    if (!strcmp(name, OSA_STDIN))
    {
        file->fp = stdin;
        file->info.f_size = 0;
    }
    else if (!strcmp(name, OSA_STDOUT))
    {
        file->fp = stdout;
        file->info.f_size = 0;
    }
    else if (!strcmp(name, OSA_STDERR))
    {
        file->fp = stderr;
        file->info.f_size = 0;
    }
    else
    {
        if ((file->fp = fopen(name, mode)) == NULL)
        {
            goto err;
        }

        h = FindFirstFile((LPCSTR)name ,&info);

        if (h != INVALID_HANDLE_VALUE)
        {
            file->info.f_size = info.nFileSizeLow;
        }
    }

    strncpy(file->info.f_name, name, OSA_NAME_MAX-1);

    return file;

err:
    osa_log_error("Failed to open file : %s\n", name);
    osa_mem_free(file);
    return NULL;
}


osa_err_t   osa_file_close(osa_file_t *file)
{
    if (file->fp)
    {
        fclose(file->fp);
    }

    file->fp = NULL;
    osa_mem_free(file);

    return OSA_ERR_OK;
}


osa_size_t    osa_file_t_read(osa_file_t *file, osa_char_t *out_buf, osa_size_t size)
{
    osa_assert(out_buf != NULL);

    if (!(file->fp))
    {
        osa_log_error("Please open file first !\n");

        return 0;
    }

    if (!(file->fp))
    {
        osa_log_error("Please open file first !\n");

        return 0;
    }

    osa_size_t sz = fread(out_buf, 1, size, file->fp);

    if (sz != size)
    {
        osa_log_warn("File read : %d bytes\n", sz);
    }

    return sz;
}


osa_size_t    osa_file_write(osa_file_t *file, const osa_char_t *buf, osa_size_t size)
{
    osa_assert(buf != NULL);

    if (!(file->fp))
    {
        osa_log_error("Please open file first!\n");

        return 0;
    }

    osa_size_t sz = fwrite(buf, 1, size, file->fp);

    if (sz != size)
    {
        osa_log_warn("File write: %d\n", sz);
    }

    return sz;
}


osa_bool_t    osa_file_is_exist(const osa_char_t *name)
{
    osa_assert(name != NULL);

    if (_access(name, 0) < 0)
    {
        return OSA_FALSE;
    }

    return OSA_TRUE;
}
