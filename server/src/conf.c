/*
 * conf.c
 *
 * Copyright (C) TuoAn
 *
 */


#include "osa.h"
#include "conf.h"
#include "conf_data.h"
#include "module.h"



static ATS_Conf    s_conf;


ATS_Conf   *ATS_ConfOpen(const char *file)
{
    osa_assert(file != NULL);

    strncpy(s_conf.file, file, OSA_NAME_MAX - 1);
    s_conf.mcf = NULL;

    return &s_conf;
}

void    ATS_ConfClose(ATS_Conf *self)
{
    s_conf.mcf = NULL;
}

void    ATS_ConfSetModuleConf(ATS_Conf *self, ATS_Module *m)
{
    self->mcf = &m->cfops;
}


osa_err_t   ATS_ConfRead(ATS_Conf *self, void *out_data)
{
    if (self->mcf->read)
    {
        return self->mcf->read(self, out_data);
    }

    return OSA_ERR_OK;
}


osa_err_t   ATS_ConfWrite(ATS_Conf *self, void *data)
{
    if (self->mcf->write)
    {
        return self->mcf->write(self, data);
    }
}
