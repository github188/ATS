/**
 *  config.h 
 *
 */
 

#ifndef __CONFIG_H__
#define __CONFIG_H__


#include "osa.h"


#ifdef __OSA_OS_WIN32__
#define ATS_CONFIG_FILE		    "C:\\ats\\ats.xml"
#define ATS_TEST_EVENT_PLUGIN	"C:\\ats\\lib\\libtevent.dll"
#endif

#ifdef __OSA_OS_LINUX__
#define ATS_CONFIG_FILE         "/etc/ats/ats.xml"
#define ATS_TEST_EVENT_PLUGIN   "/usr/lib/ats/libtevent.so"
#endif


#endif
