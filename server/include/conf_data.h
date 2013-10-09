/*
 * conf_cmd.h
 *
 * Copyright (C) TuoAn
 *
 */

#ifndef CONF_DATA_H_
#define CONF_DATA_H_

#include "osa.h"


typedef struct
{
    char            name[OSA_NAME_MAX];
    osa_uint8_t     state;
    char			testTemplete[OSA_NAME_MAX];
} CONF_Test;


typedef struct
{
    char        	name[OSA_NAME_MAX];         // 报告输出文件，可以为STDOUT
    osa_uint8_t		state;
    char			output[OSA_NAME_MAX];
} CONF_Report;


typedef struct
{
    char			name[OSA_NAME_MAX];
    osa_uint8_t		state;
    char			serverAddr[OSA_NAME_MAX];
} CONF_Erp;


typedef struct
{
    char            name[OSA_NAME_MAX];
    osa_uint8_t     state;
    osa_uint8_t     level;
    char            logFile[OSA_NAME_MAX];
} CONF_Log;

#endif /* CONF_CMD_H_ */
