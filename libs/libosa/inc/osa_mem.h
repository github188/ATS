/**
 *  osa_mem.h
 *
 */


#ifndef __OSA_MEM_H__
#define __OSA_MEM_H__


#include "osa_types.h"


#ifdef __cplusplus
extern "C"
{
#endif


#define     osa_mem_alloc(size)          _mem_alloc(size, __FILE__, __LINE__)
#define     osa_mem_realloc(ptr, size)   _MEM_Realloc(ptr, size, __FILE__, __LINE__)
#define     osa_mem_free(ptr)            free(ptr)
#define     osa_mem_zero(ptr, size)      memset(ptr, 0, size)

void    *_mem_alloc(osa_size_t  size,
                    osa_char_t  *_f, 
                    osa_uint32_t _l);
void    *_mem_realloc(void          *ptr, 
                      osa_size_t    size, 
                      osa_char_t    *_f, 
                      osa_uint32_t  _l);

#ifdef __cplusplus
}
#endif

#endif
