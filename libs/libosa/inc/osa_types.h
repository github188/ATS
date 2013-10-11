/**
 *  osa_types.h
 *
 */


#ifndef __OSA_TYPES_H__
#define __OSA_TYPES_H__


#include "osa_config.h"


#ifdef __OSA_OS_LINUX__
/** posix header */
#include <unistd.h>
/** standard I/O */
#include <stdio.h>
/** standard library */
#include <stdlib.h>
/** posix types */
#include <sys/types.h>
#endif


#ifdef __OSA_OS_WIN32__
/** windows header */
#include <windows.h>
/** standard I/O */
#include <stdio.h>
/** standard library */
#include <stdlib.h>
#endif


#ifdef __cplusplus
extern "C"
{
#endif


typedef char            osa_char_t;
typedef wchar_t         osa_wchar_t;

typedef unsigned char   osa_uint8_t;
typedef unsigned short  osa_uint16_t;
typedef unsigned int    osa_uint32_t;
typedef unsigned long long osa_uint64_t;

typedef signed char     osa_int8_t;
typedef signed short    osa_int16_t;
typedef signed int      osa_int32_t;
typedef signed long long osa_int64_t;

typedef float           osa_float_t;
typedef double          osa_double_t;

typedef osa_uint32_t    osa_ubase_t;
typedef osa_int32_t     osa_base_t;


typedef unsigned int    osa_size_t;

typedef osa_uint8_t     osa_bool_t;


// GCC supports inline in C
#if (defined(__OSA_TOOL_MINGW32__) || defined(__OSA_TOOL_GNUC__))
#define osa_inline  inline
#else
#define osa_inline
#endif


#ifndef OSA_TRUE
#define OSA_TRUE    1
#endif
#ifndef OSA_FALSE
#define OSA_FALSE   0
#endif

#ifndef NULL
#ifdef __cplusplus
#define NULL        (0L)
#else /* !__cplusplus */
#define NULL        ((void*) 0)
#endif /* !__cplusplus */
#endif

#ifndef OSA_NULL
#define OSA_NULL   NULL
#endif


#ifdef __cplusplus
}
#endif

#endif
