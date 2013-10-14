/**
 *  config.h 
 *
 */
 

#ifndef __CONFIG_H__
#define __CONFIG_H__


#include "osa.h"


#ifdef __OSA_OS_WIN32__
#define ATS_CONFIG_FILE		    "C:\\ats\\etc\\ats_win32.xml"
#define ATS_TEST_EVENT_PLUGIN	"C:\\ats\\lib\\libtevent.dll"
#define ATS_SDK_DIR             "C:\\ats\\lib\\sdk_plugins"
#endif

#ifdef __OSA_OS_LINUX__
#define ATS_CONFIG_FILE         "/opt/ats/etc/ats_linux.xml"
#define ATS_TEST_EVENT_PLUGIN   "/opt/ats/lib/libtevent.so"
#define ATS_SDK_DIR             "/opt/ats/lib/sdk_plugins"
#endif


#endif
