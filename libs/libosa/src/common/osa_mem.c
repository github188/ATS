/**
 *  osa_mem.c
 *
 */



#include "osa_types.h"
#include "osa_mem.h"
#include "osa_log.h"
#include "osa_error.h"
#include "osa_string.h"



void    *_mem_alloc(osa_size_t size, osa_char_t *_f, osa_uint32_t _l)
{
    void *p = malloc(size);
    if (!p)
    {
        osa_log_fatal("<%s, %d> Failed to allocate memory !\n", _f, _l);
    }

    memset(p, 0, size);

    return p;
}


void    *_mem_realloc(void *ptr, osa_size_t size, osa_char_t *_f, osa_uint32_t _l)
{
    void *p = realloc(ptr, size);
    if (!p)
    {
        osa_log_fatal("<%s, %d> Failed to allocate memory !\n", _f, _l);
    }

    memset(p, 0, size);

    return p;
}
