/**
 *  osa_cvt.c
 *
 */


#include "osa_types.h"
#include "osa_string.h"
#include "osa_cvt.h"
#include "osa_log.h"


OSA_API void osa_cvt_c2w(osa_char_t *src, osa_wchar_t *out_dst, osa_size_t dst_len)
{
    int clen = strlen(src);

    // get size
    osa_size_t n =(osa_size_t)MultiByteToWideChar(CP_ACP, 0, (const char *)src, clen, NULL, 0);

    if (n >= dst_len-1)
    {
        osa_log_warn("wchar data is too small!\n");

        n = dst_len - sizeof(osa_wchar_t);
    }

    MultiByteToWideChar(CP_ACP, 0, src, strlen(src), out_dst, n);

    out_dst[n] = '\0';
}

OSA_API void osa_cvt_w2c(osa_wchar_t *src, osa_char_t *out_dst, osa_size_t dst_len)
{
    int wlen=wcslen(src);

    // get length in bytes
    int nbytes = WideCharToMultiByte(0, 0, src, wlen, NULL, 0, NULL, NULL );

    if(nbytes>dst_len - 1)
    {
        osa_log_warn("char data is too small!\n");

        nbytes = dst_len -1 ;
    }

    WideCharToMultiByte(0, 0, src, wlen, out_dst, nbytes, NULL, NULL);
}
