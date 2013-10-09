/*
 * conf_xml.h
 *
 * Copyright (C) TuoAn
 *
 */

#ifndef CONF_XML_H_
#define CONF_XML_H_

#include "conf.h"
#include "conf_data.h"
#include "test_drv.h"

#include "osa.h"

#ifdef __cplusplus
extern "C" {
#endif


osa_err_t XML_TestModuleRead(ATS_Conf *cf, CONF_Test *out_data);
osa_err_t XML_ReportModuleRead(ATS_Conf *cf, CONF_Report *out_data);
osa_err_t XML_ErpModuleRead(ATS_Conf *cf, CONF_Erp *out_data);

osa_err_t XML_DevModuleParse(ATS_Conf *cf);
osa_err_t XML_LogParse(ATS_Conf *cf, CONF_Log *out_data);

osa_err_t XML_ParseTestDrvFile(ATS_TestDrv *drv);


#ifdef __cplusplus
}
#endif

#endif /* CONF_XML_H_ */
