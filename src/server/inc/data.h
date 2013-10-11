/**
 * conf_cmd.h
 *
 */

#ifndef __DATA_H__
#define __DATA_H__

#include "osa.h"


typedef struct
{
    char            name[OSA_NAME_MAX];
    osa_uint8_t     state;
    char			testTemplete[OSA_NAME_MAX];
} cf_test_t;


typedef struct
{
    char        	name[OSA_NAME_MAX];         // 报告输出文件，可以为STDOUT
    osa_uint8_t		state;
    char			output[OSA_NAME_MAX];
} cf_report_t;


typedef struct
{
    char			name[OSA_NAME_MAX];
    osa_uint8_t		state;
    char			serverAddr[OSA_NAME_MAX];
} cf_erp_t;


typedef struct
{
    char            name[OSA_NAME_MAX];
    osa_uint8_t     state;
    osa_uint8_t     level;
    char            logfile[OSA_NAME_MAX];
} cf_log_t;

#endif /* CONF_CMD_H_ */
