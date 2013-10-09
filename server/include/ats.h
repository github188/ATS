/*
 * ats.h
 *
 * Copyright (C) TuoAn
 *
 */

#ifndef ATS_H_
#define ATS_H_

#ifndef ATS_CONFIG_FILE

#ifdef __OSA_OS_WIN32__
#define ATS_CONFIG_FILE		"C:\\ats\\ats.xml"
#endif

#ifdef __OSA_OS_LINUX__
#define ATS_CONFIG_FILE     "/etc/ats/ats.xml"
#endif

#endif


typedef struct _ATS_MODULE_CONF_OPS ATS_ModuleConfOps;
typedef struct _ATS_CONF            ATS_Conf;
typedef struct _ATS_MODULE          ATS_Module;
typedef struct _ATS_TEST_EVENT      ATS_TestEvent;
typedef struct _ATS_TEST_CASE_BOX   ATS_TestCaseBox;
typedef struct _ATS_DEVICE          ATS_Device;
typedef struct _ATS_TEST_DRIVER     ATS_TestDrv;
typedef struct _ATS_DEVICE_BUS      ATS_DevBus;
typedef struct _ATS_REPORT_ITR      ATS_Report;


extern ATS_Conf  *g_conf;


#endif /* ATS_H_ */
