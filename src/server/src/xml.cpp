/**
 * xml.cpp
 *
 */


#include "tinyxml.h"
#include "xml.h"
#include "core.h"
#include "test_event.h"


#ifdef __cplusplus
extern "C" {
#endif


static TiXmlElement *get_module_root(const char *xmlfile, const char *node_name)
{
    osa_assert(xmlfile != NULL);
    osa_assert(node_name != NULL);

    if (osa_file_is_exist(xmlfile) != OSA_TRUE)
    {
        ats_log_error("File not exist: %s!\n", xmlfile);
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
    TiXmlElement *mroot = NULL;
    const char *tmp = NULL;

    do
    {
        mroot = get_module_root(cf, "report");
        if (!mroot) break;

        tmp = mroot->FirstChildElement("state")->FirstChild()->Value();
        if (!tmp) break;
        out_data->state = (strcmp(tmp, "on") == 0)? ATS_ON : ATS_OFF;

        strncpy(out_data->name, "report", OSA_NAME_MAX-1);

        return OSA_ERR_OK;
    } while(0);

    delete mroot;

    osa_log_error("Error when parse configuration file : %s\n", cf);
    return OSA_ERR_ERR;
}


osa_err_t xml_parse_log_conf(const osa_char_t *cf, cf_log_t *out_data)
{
    TiXmlElement    *mroot = NULL;
    const char *tmp = NULL;

    do
    {
        mroot = get_module_root(cf, "log");
        if (!mroot) break;

        tmp = mroot->FirstChildElement("state")->FirstChild()->Value();
        if (!tmp) break;
        out_data->state = (strcmp(tmp, "on") == 0)? ATS_ON : ATS_OFF;

        tmp = mroot->FirstChildElement("level")->FirstChild()->Value();
        if (!tmp) break;
        out_data->level = atoi(tmp);

        tmp = mroot->FirstChildElement("file")->FirstChild()->Value();
        if (!tmp) break;
        strncpy(out_data->logfile, tmp, OSA_NAME_MAX-1);

        strncpy(out_data->name, "log", OSA_NAME_MAX-1);

        return OSA_ERR_OK;
    } while(0);

    delete mroot;

    ats_log_error("Error occured when parse configuration file : %s\n", cf);
    return OSA_ERR_ERR;
}


osa_err_t xml_parse_test_conf(const osa_char_t *cf, cf_test_t *out_data)
{
    TiXmlElement    *mroot = NULL;
    const char *tmp = NULL;

    do
    {
        mroot = get_module_root(cf, "test");
        if (!mroot) break;

        tmp = mroot->FirstChildElement("state")->FirstChild()->Value();
        if (!tmp) break;
        out_data->state = (strcmp(tmp, "on") == 0)? ATS_ON : ATS_OFF;

        strncpy(out_data->name, "test", OSA_NAME_MAX-1);

        return OSA_ERR_OK;
    } while (0);

    delete mroot;

    ats_log_error("Error occured when parse configuration file : %s\n", cf);
    return OSA_ERR_ERR;
}



#ifdef __cplusplus
}
#endif
