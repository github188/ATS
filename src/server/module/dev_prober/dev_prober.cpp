/**
 *  dev_prober.cpp
 *
 */

#include "osa.h"
#include "tinyxml.h"
#include "core.h"
#include "config.h"
#include "module/dev_prober.h"


#ifdef __cplusplus
extern "C"
{
#endif

#define DEV_MAX     20

static ats_device_t dev[DEV_MAX];
static osa_uint32_t idx = 0;

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

osa_err_t ats_devpb_init()
{
    if (idx >= DEV_MAX)
    {
        return OSA_ERR_ERR;
    }
    
    TiXmlElement *mroot = get_module_root(ATS_CONFIG_FILE, "device");
    osa_assert(mroot != NULL);

    TiXmlElement    *dev_node = NULL;
    TiXmlElement    *info_node = NULL;
    TiXmlElement    *tmp = NULL;

    const char 		*dev_name = NULL;
    ats_devtype_t   dev_type = DT_DUMMY;
    const char 		*addr = NULL;
    const char 		*user = NULL;
    const char 		*password = NULL;
    const char		*drv_file = NULL;
    const char		*sdk_plugin = NULL;

    dev_node = mroot->FirstChildElement("device");
    osa_assert(dev_node != NULL);

    while (dev_node)
    {
        info_node = dev_node->FirstChildElement("info");
        osa_assert(info_node != NULL);

        dev_name = dev_node->Attribute("name");
        osa_assert(dev_name != NULL);

        dev_type = (ats_devtype_t)atoi(dev_node->Attribute("type"));
        osa_assert(dev_type > 0);

        tmp = info_node->FirstChildElement("addr");
        osa_assert(tmp != NULL);
        addr = (tmp->FirstChild()) ? tmp->FirstChild()->Value(): NULL;

        tmp = info_node->FirstChildElement("user");
        osa_assert(tmp != NULL);
        user = (tmp->FirstChild()) ? tmp->FirstChild()->Value(): NULL;

        tmp = info_node->FirstChildElement("password");
        osa_assert(tmp != NULL);
        password = (tmp->FirstChild()) ? tmp->FirstChild()->Value(): NULL;

        tmp = dev_node->FirstChildElement("drv_file");
        osa_assert(tmp != NULL);
        drv_file = (tmp->FirstChild()) ? tmp->FirstChild()->Value(): NULL;

        tmp = dev_node->FirstChildElement("sdk_plugin");
        osa_assert(tmp != NULL);
        sdk_plugin = (tmp->FirstChild()) ? tmp->FirstChild()->Value(): NULL;
      
        /** device init */
        if (dev_name)
            strncpy(dev[idx].name, dev_name, strlen(dev_name));
        if (drv_file)
            strncpy(dev[idx].drv_file, drv_file, strlen(drv_file));
        if (sdk_plugin)
            strncpy(dev[idx].sdk_plugin, sdk_plugin, strlen(sdk_plugin));
        ats_devinfo_set(&dev[idx].info, dev_type, addr, user, password);

        idx++;
        dev_node = dev_node->NextSiblingElement("device");
    }
    
    delete mroot;
    
	return OSA_ERR_OK;
}

void ats_devpb_probe()
{
    ats_bus_t   *dev_bus = ats_bus_find("dev_bus");
    if (!dev_bus)
    {
        ats_log_error("No device bus find!\n");
    }

    ats_devpb_t     *dp = NULL;
    osa_uint32_t    i = 0;
    
    for (i=0; i<idx; i++)
    {
        dp = ats_devpb_obtain(dev[i].name);
        if (!dp)
        {
            ats_log_warn("No suitable prober for device(%s)!\n", dev[i].name);
            continue;
        }
        
        if (dp->dev_is_ok(&dev[i].info) !=OSA_TRUE)
        {
            ats_device_unregister(dev_bus, dev[i].name);
            continue;
        }
        
        if (ats_device_find(dev_bus, dev[i].name) == NULL)
        {
            ats_device_t *new_dev = ats_device_new(dev[i].name);
            ats_devinfo_set(&new_dev->info, 
                            dev[i].info.type, 
                            dev[i].info.addr.addr, 
                            dev[i].info.user, 
                            dev[i].info.passwd);
            
            if (dev[i].drv_file[0] !='\0' &&
                ats_device_load_tdrv(new_dev, dev[i].drv_file) != OSA_ERR_OK)
            {
                ats_log_warn("Failed to load test driver for device: %s\n", new_dev->name);
            }
            
            if (dev[i].sdk_plugin[0] !='\0' && 
                ats_device_load_sdk(new_dev, dev[i].sdk_plugin) != OSA_ERR_OK)
            {
                ats_log_warn("Failed to load sdk plugin for device :%s\n", new_dev->name);
            }
            
            ats_device_print(new_dev);
            ats_device_register(dev_bus, new_dev);
        }
    }
}

ats_devpb_t *ats_devpb_obtain(const osa_char_t *dev_name)
{
    osa_uint32_t i = 0;
    ats_devpb_t *dp = NULL;
    
    // 找到设备探测器
    for (i=0; i<g_dpnum; i++)
    {
        dp = g_dptable[i];
        if (ats_devpb_is_support(dp, dev_name) == OSA_TRUE)
        {
            return dp;
            break;
        }
    }
    
    return NULL;
}

osa_bool_t ats_devpb_is_support(ats_devpb_t *dp, const osa_char_t *dev_name)
{
    osa_assert(dev_name != NULL);

    if (!dp->dev_support)
    {
        return OSA_FALSE;
    }

    char *devs = (char *)osa_mem_alloc(strlen(dp->dev_support)+1);
    strncpy(devs, dp->dev_support, strlen(dp->dev_support));

    char *p = strtok(devs, ",");
    while (p != NULL)
    {
        if (!strcmp(p, dev_name))
        {
            osa_mem_free(devs);
            return OSA_TRUE;
        }
        p = strtok(NULL, ",");
    }
    osa_mem_free(devs);
    return OSA_FALSE;
}

#ifdef __cplusplus
}
#endif
