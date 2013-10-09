/**
 *  osa_dll.c
 *
 */


 
#include "osa_types.h"
#include "osa_dll.h"
#include "osa_log.h"
#include "osa_error.h"

#include <dlfcn.h>


osa_err_t   osa_dll_load(osa_dll_t *dll, const osa_char_t *file)
{
    osa_assert(file != NULL);

    if ((dll->handler=dlopen(file, RTLD_LAZY | RTLD_LOCAL)) == NULL)
    {
        osa_log_error("Failed to load library : file(%s), %s\n", file, dlerror());
        return OSA_ERR_ERR;
    }

    return OSA_ERR_OK;
}

osa_err_t   osa_dll_unload(osa_dll_t *dll)
{
    if (dll->handler)
    {
        dlclose(dll->handler);
    }
    dll->handler = NULL;
    return OSA_ERR_OK;
}

void        *osa_dll_sym(osa_dll_t *dll, const osa_char_t *symbol)
{
    osa_assert(symbol != NULL);

    void *p = dlsym(dll->handler, symbol);
    if (!p)
    {
        osa_log_error("No symbol found: %s\n", symbol);
    }
    return p;
}
