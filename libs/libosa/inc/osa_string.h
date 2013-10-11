/**
 *  osa_string.h
 *
 */

#ifndef __OSA_STRING_H__
#define __OSA_STRING_H__


#include "osa_types.h"
#include <string.h>


#ifdef __cplusplus
extern "C"
{
#endif


typedef struct _OSA_STRING
{
    osa_char_t        *str;
    osa_size_t        len;
} osa_string_t;



osa_inline static void osa_string_set(osa_string_t *string, osa_char_t *str)
{
    string->str = str;
    string->len = strlen(str);
}

osa_inline static osa_char_t *osa_string_get(osa_string_t *string)
{
    return string->str;
}


#ifdef __cplusplus
}
#endif

#endif
