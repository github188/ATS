/**
 *  osa_dll.h
 *
 */


#ifndef __OSA_DLL_H__
#define __OSA_DLL_H__

#include "osa_types.h"
#include "osa_error.h"


#ifdef __OSA_OS_LINUX__
#include <dlfcn.h>
typedef     void    *dll_handler_t;
#endif

#ifdef __OSA_OS_WIN32__
typedef     HMODULE dll_handler_t;
#endif


typedef struct _OSA_DLL
{
    dll_handler_t   handler;
} osa_dll_t;



OSA_API osa_err_t   osa_dll_load(osa_dll_t *dll, const osa_char_t *file);
OSA_API osa_err_t   osa_dll_unload(osa_dll_t *dll);
OSA_API void        *osa_dll_sym(osa_dll_t *dll, const osa_char_t *symbol);


#endif
