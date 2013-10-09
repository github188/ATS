/*
 * module.c
 *
 * Copyright (C) TuoAn
 *
 */


#include "osa.h"
#include "module.h"
#include "log.h"

// 模块容器
ATS_Module  *mBox[ATS_MODULE_MAX] = {NULL};


ATS_Module *ATS_ModuleFind(const char *name)
{
    osa_assert(name != NULL);

    ATS_Module  *m = NULL;
    osa_uint32_t    i;

    for (i=0; i<ATS_MODULE_MAX; i++)
    {
        if (mBox[i] && !strcmp(mBox[i]->name, name))
        {
            m = mBox[i];
            break;
        }
    }

#if 0
    if (i == ATS_MODULE_MAX)
    {
        ATS_LogWarn("Module not found : name(%s)\n", name);
    }
#endif

    return m;
}


osa_err_t ATS_ModuleRegister(ATS_Module *module)
{
    ATS_Module  *p = NULL;
    osa_err_t   err;

    ATS_LogInfo("Register module: name(%s)\n", module->name);

    if ((p = ATS_ModuleFind(module->name)) != NULL)
    {
        ATS_LogWarn("Replace module: name(%s)\n", module->name);
        p = module;
        err = OSA_ERR_OK;
    }
    else
    {
        osa_uint32_t    i;

        for (i=0; i<ATS_MODULE_MAX; i++)
        {
            if (!mBox[i])
            {
                mBox[i] = module;
                err = OSA_ERR_OK;
                break;
            }
        }

        if (i == ATS_MODULE_MAX)
        {
            ATS_LogError("No space for module registration!\n");
            err = OSA_ERR_ERR;
        }
    }

    return err;
}


osa_err_t ATS_ModuleUnregister(ATS_Module *module)
{
    ATS_Module  *p = NULL;

    if ((p = ATS_ModuleFind(module->name)) != NULL)
    {
        p = NULL;
    }

    ATS_LogInfo("Unregister module : name(%s)\n", module->name);
    return OSA_ERR_OK;
}


void    ATS_ModuleInitAll(int argc, char **argv)
{
    osa_uint32_t i;
    osa_err_t   err;

    for (i=0; i<ATS_MODULE_MAX; i++)
    {
        if (mBox[i] && mBox[i]->entry)
        {
            ATS_LogInfo("Initialize module: name(%s)\n", mBox[i]->name);

            err = mBox[i]->entry(mBox[i]->cf, argc, argv);
            if (err != OSA_ERR_OK)
            {
                ATS_LogError("Failed to initialize module : name(%s)\n", mBox[i]->name);
            }
        }
    }
}
