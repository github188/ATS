/**
 *  osa_macro.h
 *
 */


#ifndef __OSA_MACRO_H__
#define __OSA_MACRO_H__


#ifdef __cplusplus
extern "C"
{
#endif


#define     OSA_MAX(a, b)   (((a) > (b))? (a): (b))

#define     OSA_MIN(a, b)   (((a) < (b))? (a): (b))

#define     OSA_STRUCT_ENTRY(node, type, member)    \
     ((type *)((char *)(node) - (unsigned long)(&((type *)0)->member)))


#ifdef __cplusplus
}
#endif


#endif

