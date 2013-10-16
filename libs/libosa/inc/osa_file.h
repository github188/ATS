/**
 *  osa_file.h
 *
 */


#ifndef __OSA_FILE_H__
#define __OSA_FILE_H__


#include "osa_types.h"
#include "osa_error.h"
#include "osa_config.h"


#ifdef __cplusplus
extern "C"
{
#endif


#ifdef __OSA_OS_LINUX__
typedef osa_int32_t     osa_fd_t;
#endif

#ifdef __OSA_OS_WIN32__
typedef HANDLE          osa_fd_t;
#endif


#define     OSA_STDIN       "stdin"
#define     OSA_STDOUT      "stdout"
#define     OSA_STDERR      "stderr"


typedef struct
{
    osa_char_t    f_name[OSA_NAME_MAX];
    osa_size_t    f_size;
} osa_file_info;


typedef struct
{
    FILE                *fp;
    osa_file_info       info;
} osa_file_t;


#define    OSA_F_RDONLY     "r"
#define    OSA_F_WRONLY     "w"
#define    OSA_F_RDWR       "w+"
#define    OSA_F_APPEND     "a"


OSA_API osa_file_t    *osa_file_open(const osa_char_t   *name,
                                     osa_char_t         *mode);
OSA_API osa_err_t     osa_file_close(osa_file_t     *file);
OSA_API osa_size_t    osa_file_read(osa_file_t      *file, 
                                    osa_char_t      *out_buf, 
                                    osa_size_t      size);
OSA_API osa_size_t    osa_file_write(osa_file_t     *file,
                                     const osa_char_t *buf, 
                                     osa_size_t     size);
OSA_API osa_bool_t    osa_file_is_exist(const osa_char_t *name);
OSA_API osa_err_t     osa_file_rename(const osa_char_t  *nfile, 
                                      const osa_char_t  *ofile);
OSA_API osa_err_t     osa_file_delete(const osa_char_t *name);

OSA_API const osa_char_t *osa_file_suffix(const osa_char_t *name);


#ifdef __cplusplus
}
#endif

#endif
