/*
 * conf_xml.cpp
 *
 * Copyright (C) TuoAn
 *
 */


#include "conf_xml.h"
#include "tinyxml.h"
#include "log.h"
#include "module.h"
#include "test_drv.h"
#include "dev_bus.h"


#ifdef __cplusplus
extern "C" {
#endif


TiXmlElement *_getModuleRoot(char *xmlfile, const char *node_name)
{
    osa_assert(xmlfile != NULL);
    osa_assert(node_name != NULL);

    if (osa_file_is_exist(xmlfile) != OSA_TRUE)
    {
        ATS_LogError("File not exist!\n", xmlfile);
        return NULL;
    }

    TiXmlDocument   *doc = new TiXmlDocument(xmlfile);
    TiXmlElement    *root = NULL;

    if (doc->LoadFile()!=true)
    {
        ATS_LogError("Failed to load xml: %s\n", xmlfile);
        return NULL;
    }

    if ((root = doc->RootElement())==NULL)
    {
        ATS_LogError("Failed to get xml root: %s\n", xmlfile);
        return NULL;
    }

    TiXmlElement    *tmp = root->FirstChildElement("module");
    TiXmlAttribute  *attr = NULL;

    while (tmp)
    {
        attr = tmp->FirstAttribute();
        osa_assert(attr != NULL);

        if (!strcmp(attr->Value(), node_name))
        {
            return tmp;
        }
        tmp = tmp->NextSiblingElement("module");
    }

    return NULL;
}


osa_err_t XML_ReportModuleRead(ATS_Conf *cf, CONF_Report *out_data)
{
    TiXmlElement    *moduleRoot = NULL;
    TiXmlElement    *node       = NULL;

    moduleRoot = _getModuleRoot(cf->file, "report");
    if (!moduleRoot)
    {
        ATS_LogError("Failed to get module xml root!\n");
        goto err;
    }

    strncpy(out_data->name, "report", OSA_NAME_MAX-1);

    node = moduleRoot->FirstChildElement("state");
    if (!node)
    {
        ATS_LogError("Node not found: state!\n");
        goto err;
    }
    if (!strcmp(node->FirstChild()->Value(), "on"))
    {
        out_data->state = ATS_MODULE_ON;
    }
    else
    {
        out_data->state = ATS_MODULE_OFF;
    }

    return OSA_ERR_OK;

err:
    ATS_LogError("Error occured when parse xml\n");
    return OSA_ERR_ERR;
}


osa_err_t XML_LogParse(ATS_Conf *cf, CONF_Log *out_data)
{
    TiXmlElement    *moduleRoot = NULL;
    TiXmlElement    *node       = NULL;

    moduleRoot = _getModuleRoot(cf->file, "log");
    if (!moduleRoot)
    {
        ATS_LogError("Failed to get module xml root!\n");
        goto err;
    }

    strncpy(out_data->name, "log", OSA_NAME_MAX-1);

    node = moduleRoot->FirstChildElement("state");
    if (!node)
    {
        ATS_LogError("Node not found: state!\n");
        goto err;
    }
    if (!strcmp(node->FirstChild()->Value(), "on"))
    {
        out_data->state = ATS_MODULE_ON;
    }
    else
    {
        out_data->state = ATS_MODULE_OFF;
    }

    node = moduleRoot->FirstChildElement("level");
    if (!node)
    {
        ATS_LogError("Node not found: level!\n");
        goto err;
    }
    out_data->level = atoi(node->FirstChild()->Value());

    node = moduleRoot->FirstChildElement("file");
    if (!node)
    {
        ATS_LogError("Node not found: file!\n");
        goto err;
    }
    strncpy(out_data->logFile, node->FirstChild()->Value(), OSA_NAME_MAX-1);

    return OSA_ERR_OK;

err:
    ATS_LogError("Error occured when parse xml\n");
    return OSA_ERR_ERR;
}


osa_err_t XML_TestModuleRead(ATS_Conf *cf, CONF_Test *out_data)
{
    TiXmlElement    *moduleRoot = NULL;
    TiXmlElement    *node       = NULL;

    moduleRoot = _getModuleRoot(cf->file, "test");
    if (!moduleRoot)
    {
        ATS_LogError("Failed to get module xml root!\n");
        goto err;
    }

    strncpy(out_data->name, "test", OSA_NAME_MAX-1);

    node = moduleRoot->FirstChildElement("state");
    if (!node)
    {
        ATS_LogError("Node not found: state!\n");
        goto err;
    }
    if (!strcmp(node->FirstChild()->Value(), "on"))
    {
        out_data->state = ATS_MODULE_ON;
    }
    else
    {
        out_data->state = ATS_MODULE_OFF;
    }

    return OSA_ERR_OK;

err:
    ATS_LogError("Error occured when parse xml\n");
    return OSA_ERR_ERR;
}


osa_err_t XML_DevModuleParse(ATS_Conf *cf)
{
    TiXmlElement    *moduleRoot = NULL;
    TiXmlElement    *node       = NULL;

    moduleRoot = _getModuleRoot(cf->file, "device");
    if (!moduleRoot)
    {
        ATS_LogError("Failed to get module xml root!\n");
        return OSA_ERR_ERR;
    }

    TiXmlAttribute  *attr = NULL;
    ATS_TestDrv *tdv = NULL;

    node = moduleRoot->FirstChildElement("file");

    while (node)
    {
        attr = node->FirstAttribute();
        osa_assert(attr != NULL);

        tdv = ATS_TestDrvNew(attr->Value(), node->FirstChild()->Value());

        // 挂接测试驱动到设备总线
        ATS_DevBusHangDrv(tdv);

        node = node->NextSiblingElement("file");
    }

    return OSA_ERR_OK;
}


osa_err_t XML_ParseTestDrvFile(ATS_TestDrv *drv)
{
    TiXmlElement    *moduleRoot = NULL;
    TiXmlElement    *node       = NULL;

    if (osa_file_is_exist(drv->cf) != OSA_TRUE)
    {
        ATS_LogError("File not exist: %s\n", drv->cf);
        return OSA_ERR_ERR;
    }

    TiXmlDocument   doc(drv->cf);
    if (doc.LoadFile() != true)
    {
        ATS_LogError("Failed to load file : name(%s)\n", drv->cf);
        return OSA_ERR_ERR;
    }

    TiXmlElement    *root = doc.RootElement();
    if (!root)
    {
        ATS_LogError("XML root not found!\n");
        return OSA_ERR_ERR;
    }

    TiXmlAttribute      *attr = NULL;
    ATS_TestEvent       *tp = NULL;
    const osa_char_t    *tpName=NULL;

    node = root->FirstChildElement("test_event");

    while (node)
    {
        attr = node->FirstAttribute();
        osa_assert(attr != NULL);
        if (strcmp(attr->Name(), "name"))
        {
            ATS_LogWarn("XML file error!\n");
            node = node->NextSiblingElement("test_event");
            continue;
        }

        if ((tp = ATS_TestEventFind(attr->Value())) == NULL)
        {
            ATS_LogError("TestPoint not found : name(%s)\n", attr->Value());
            node = node->NextSiblingElement("test_event");
            continue;
        }

        ATS_TestDrvRegisterTestEvent(drv, tp);

        node = node->NextSiblingElement("test_event");
    }

    return OSA_ERR_OK;
}


#ifdef __cplusplus
}
#endif
