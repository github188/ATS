/**
 *  config.h 
 *
 */
 

#ifndef __CONFIG_H__
#define __CONFIG_H__


#include "osa.h"


#ifdef __OSA_OS_WIN32__
#define ATS_CONFIG_FILE		"C:\\ats\\ats.xml"
#define TEST_POINT_PLUGIN	"C:\\ats\\lib\\libtp.dll"
#endif

#ifdef __OSA_OS_LINUX__
#define ATS_CONFIG_FILE     "/etc/ats/ats.xml"
#define TEST_POINT_PLUGIN   "/usr/lib/ats/libtp.so"
#endif


#endif
