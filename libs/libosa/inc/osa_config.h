/**
 *  osa_config.h
 *
 */


#ifndef __OSA_CONFIG_H__
#define __OSA_CONFIG_H__


#ifdef __cplusplus
extern "C"
{
#endif


//#define __WIN32__


#if (defined(__WIN32__) || defined(_WIN32) || defined(WIN32))
#define __OSA_OS_WIN32__
#undef  __OSA_OS_LINUX__
#else
#define __OSA_OS_LINUX__
#undef  __OSA_OS_WIN32__
#endif


#ifdef __OSA_OS_WIN32__
#if (defined(__MINGW32__) || defined(MINGW32))
#define __OSA_TOOL_MINGW32__
#else
#define __OSA_TOOL_MSVS__
#endif
#endif


#ifdef __OSA_OS_LINUX__
#define __OSA_TOOL_GNUC__
#endif


#if (defined(__OSA_TOOL_MINGW32__) || defined(__OSA_TOOL_GNUC__))
#define OSA_API
#endif

#if (defined(__OSA_TOOL_MSVS__))
#define OSA_API extern "C" __declspec(dllexport)
#endif



#ifdef  __OSA_OS_LINUX__
#define     OSA_NAME_MAX    128
#endif

#ifdef __OSA_OS_WIN32__
#include <stdlib.h>
#define     OSA_NAME_MAX    MAX_PATH
#endif


#ifdef __cplusplus
}
#endif

#endif
