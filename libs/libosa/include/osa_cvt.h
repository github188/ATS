/**
 *  osa_cvt.h
 *
 */


#ifndef __OSA_CVT_H__
#define __OSA_CVT_H__

#include "osa_types.h"

#ifdef __cplusplus
extern "C"
{
#endif

// char to wchar(windows)
OSA_API void osa_cvt_c2w(osa_char_t *src, osa_wchar_t *out_dst, osa_size_t dst_len);

OSA_API void osa_cvt_w2c(osa_wchar_t *src, osa_char_t *out_dst, osa_size_t dst_len);



#ifdef __cplusplus
}
#endif


#endif