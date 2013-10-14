/*
 * xml.h
 *
 */

#ifndef __XML_H__
#define __XML_H__


#include "data.h"
#include "test_drv.h"

#include "osa.h"

#ifdef __cplusplus
extern "C" {
#endif


osa_err_t xml_parse_test_conf(const osa_char_t *cf, cf_test_t *out_data);
osa_err_t xml_parse_report_conf(const osa_char_t *cf, cf_report_t *out_data);
osa_err_t xml_parse_erp_conf(const osa_char_t *cf, cf_erp_t *out_data);
osa_err_t xml_parse_log_conf(const osa_char_t *cf, cf_log_t *out_data);

osa_err_t xml_parse_drvfile(ats_tdrv_t *tdrv);


#ifdef __cplusplus
}
#endif

#endif /* CONF_XML_H_ */
