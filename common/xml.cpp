/**
 *  xml.cpp
 *
 */
 
 
#include "osa.h"
#include "core.h"
#include "tinyxml.h"


#ifdef __cplusplus
extern "C"
{
#endif


osa_err_t xml_parse_drvfile(ats_tdrv_t *tdrv, const osa_char_t *drv_file)
{
    if (osa_file_is_exist(drv_file) != OSA_TRUE)
    {
        ats_log_error("Driver file(%s) not exist!\n", drv_file);
        return OSA_ERR_ERR;
    }
    
    TiXmlElement    *node       = NULL;

    TiXmlDocument   doc(drv_file);
    if (doc.LoadFile() != true)
    {
        ats_log_error("Failed to load file : name(%s)\n", drv_file);
        return OSA_ERR_ERR;
    }

    TiXmlElement    *root = doc.RootElement();
    if (!root)
    {
        ats_log_error("XML root not found!\n");
        return OSA_ERR_ERR;
    }

    const char 		*tmp = NULL;
    ats_tevent_t    *tevent = NULL;

    node = root->FirstChildElement("test_event");

    while (node)
    {
        tmp = node->Attribute("name");
        if (!tmp) continue;

        if ((tevent = ats_tevent_get(tmp)) != NULL)
        {
            ats_tevent_register(tdrv, tevent);
        }
		else
		{
			ats_log_warn("No test event (%s) found in test event plugin!\n", tmp);
		}

        node = node->NextSiblingElement("test_event");
    }

    return OSA_ERR_OK;
}


#ifdef __cplusplus
}
#endif
