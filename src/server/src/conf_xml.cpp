/**
 * conf_xml.cpp
 *
 */


#include "conf_xml.h"
#include "tinyxml.h"
#include "log.h"
#include "module.h"
#include "test_drv.h"


#ifdef __cplusplus
extern "C" {
#endif


TiXmlElement *get_module_root(char *xmlfile, const char *node_name)
{
    osa_assert(xmlfile != NULL);
    osa_assert(node_name != NULL);

    if (osa_file_is_exist(xmlfile) != OSA_TRUE)
    {
        ats_log_error("File not exist!\n", xmlfile);
        return NULL;
    }

    TiXmlDocument   *doc = new TiXmlDocument(xmlfile);
    TiXmlElement    *root = NULL;

    if (doc->LoadFile()!=true)
    {
        ats_log_error("Failed to load xml: %s\n", xmlfile);
        return NULL;
    }

    if ((root = doc->RootElement())==NULL)
    {
        ats_log_error("Failed to get xml root: %s\n", xmlfile);
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


osa_err_t xml_parse_report_conf(const osa_char_t *cf, cf_report_t *out_data)
{
    TiXmlElement    *moduleRoot = NULL;
    TiXmlElement    *node       = NULL;

    moduleRoot = get_module_root(cf, "report");
    if (!moduleRoot)
    {
        ats_log_error("Failed to get module xml root!\n");
        goto err;
    }

    strncpy(out_data->name, "report", OSA_NAME_MAX-1);

    node = moduleRoot->FirstChildElement("state");
    if (!node)
    {
        ats_log_error("Node not found: state!\n");
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
    ats_log_error("Error occured when parse xml\n");
    return OSA_ERR_ERR;
}


osa_err_t xml_parse_log_conf(const osa_char_t *cf, cf_log_t *out_data)
{
    TiXmlElement    *moduleRoot = NULL;
    TiXmlElement    *node       = NULL;

    moduleRoot = get_module_root(cf, "log");
    if (!moduleRoot)
    {
        ats_log_error("Failed to get module xml root!\n");
        goto err;
    }

    strncpy(out_data->name, "log", OSA_NAME_MAX-1);

    node = moduleRoot->FirstChildElement("state");
    if (!node)
    {
        ats_log_error("Node not found: state!\n");
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
        ats_log_error("Node not found: level!\n");
        goto err;
    }
    out_data->level = atoi(node->FirstChild()->Value());

    node = moduleRoot->FirstChildElement("file");
    if (!node)
    {
        ats_log_error("Node not found: file!\n");
        goto err;
    }
    strncpy(out_data->logfile, node->FirstChild()->Value(), OSA_NAME_MAX-1);

    return OSA_ERR_OK;

err:
    ats_log_error("Error occured when parse xml\n");
    return OSA_ERR_ERR;
}


osa_err_t xml_parse_test_conf(const osa_char_t *cf, cf_test_t *out_data)
{
    TiXmlElement    *moduleRoot = NULL;
    TiXmlElement    *node       = NULL;

    moduleRoot = get_module_root(cf, "test");
    if (!moduleRoot)
    {
        ats_log_error("Failed to get module xml root!\n");
        goto err;
    }

    strncpy(out_data->name, "test", OSA_NAME_MAX-1);

    node = moduleRoot->FirstChildElement("state");
    if (!node)
    {
        ats_log_error("Node not found: state!\n");
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
    ats_log_error("Error occured when parse xml\n");
    return OSA_ERR_ERR;
}


osa_err_t xml_parse_dev_conf(const osa_char_t *cf)
{
    TiXmlElement    *moduleRoot = NULL;
    TiXmlElement    *node       = NULL;

    moduleRoot = get_module_root(cf, "device");
    if (!moduleRoot)
    {
        ats_log_error("Failed to get module xml root!\n");
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


osa_err_t xml_parse_tdrvfile(ats_tdrv_t *tdrv)
{
    TiXmlElement    *moduleRoot = NULL;
    TiXmlElement    *node       = NULL;

    if (osa_file_is_exist(tdrv->drv_file) != OSA_TRUE)
    {
        ats_log_error("File not exist: %s\n", tdrv->drv_file);
        return OSA_ERR_ERR;
    }

    TiXmlDocument   doc(tdrv->drv_file);
    if (doc.LoadFile() != true)
    {
        ats_log_error("Failed to load file : name(%s)\n", tdrv->drv_file);
        return OSA_ERR_ERR;
    }

    TiXmlElement    *root = doc.RootElement();
    if (!root)
    {
        ats_log_error("XML root not found!\n");
        return OSA_ERR_ERR;
    }

    TiXmlAttribute      *attr = NULL;
    ats_tevent_t        *te = NULL;
    const osa_char_t    *tpName=NULL;

    node = root->FirstChildElement("test_event");

    while (node)
    {
        attr = node->FirstAttribute();
        osa_assert(attr != NULL);
        if (strcmp(attr->Name(), "name"))
        {
            ats_log_warn("XML file error!\n");
            node = node->NextSiblingElement("test_event");
            continue;
        }

        if ((te = ats_tevent_get(attr->Value())) == NULL)
        {
            ats_log_error("TestPoint not found : name(%s)\n", attr->Value());
            node = node->NextSiblingElement("test_event");
            continue;
        }

        ats_tevent_register(tdrv, te);

        node = node->NextSiblingElement("test_event");
    }

    return OSA_ERR_OK;
}


#ifdef __cplusplus
}
#endif
