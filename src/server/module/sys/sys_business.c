/**
 *  sys_business.c
 *
 */


#include "sys_business.h"
#include "osa.h"
#include "log.h"
#include "cJSON.h"
#include "test_drv.h"
#include "device.h"
#include "bus.h"
#include "test_event.h"
#include "module/test.h"
#include "module/report.h"


osa_bool_t  devLocked = OSA_FALSE;

osa_err_t   sysLogin(osa_ioch_t *ioch, osa_msg_t *msg)
{
    ats_log_info("Login system ....\n");

    osa_err_t  result = OSA_ERR_ERR;

    if (!msg->data)
    {
        return OSA_ERR_ERR;
    }

    cJSON *root = cJSON_Parse(msg->data);
    if (!root)
    {
        ats_log_error("Failed to create json root object!\n");
        return OSA_ERR_ERR;
    }

    cJSON *user = cJSON_GetObjectItem(root,  "user");
    cJSON *passwd = cJSON_GetObjectItem(root, "password");

    if (!strcmp("\"admin\"", cJSON_Print(user)) && !strcmp("\"admin\"", cJSON_Print(passwd)))
    {
        ats_log_info("Login success : user(%s), password(%s)\n", user->valuestring, passwd->valuestring);
        result = OSA_ERR_OK;
    }

    osa_msg_t *retmsg = osa_msg_new_with_data(msg->header.id, "RET:LoginSystem", NULL, 0);
    osa_msg_set_result(retmsg, result);

    osa_msg_send(ioch, retmsg);

    osa_msg_dump(retmsg);

    osa_msg_delete(retmsg);
    cJSON_Delete(root);

    return OSA_ERR_OK;
}


osa_err_t   sysGetDevs(osa_ioch_t *ioch, osa_msg_t *msg)
{
    ats_log_info("Get camera devices!\n");

    ats_device_t *node  = NULL;
    osa_list_t *l = NULL;
    osa_size_t  cnt = 0;

    ats_bus_t   *devbus = ats_bus_find("dev_bus");
    if (!devbus)
    {
        ats_log_error("device bus not found!\n");
        return OSA_ERR_ERR;
    }

    cJSON *root = cJSON_CreateObject();
    if (!root)
    {
        ats_log_error("Failed to create json root!\n");
        return OSA_ERR_ERR;
    }

    cJSON *devArray = cJSON_CreateArray();
    if (!devArray)
    {
        ats_log_error("Failed to create json array!\n");
        return OSA_ERR_ERR;
    }

    cJSON *dev = NULL;
    for (l=devbus->ele_list_head.next; l!=&devbus->ele_list_head; l=l->next)
    {
        node = osa_list_entry(l, ats_device_t, list);
        cJSON_AddItemToArray(devArray, dev=cJSON_CreateObject());

        cJSON_AddStringToObject(dev, "name", node->name);
        cJSON_AddStringToObject(dev, "ip", node->info.addr.net_addr.ip);
        cJSON_AddNumberToObject(dev, "port", node->info.addr.net_addr.port);
        cJSON_AddStringToObject(dev, "company", node->info.company);

        cnt++;
    }
    cJSON_AddNumberToObject(root, "dev_num", cnt);
    cJSON_AddItemToObject(root, "devs", devArray);

    osa_char_t *data = cJSON_Print(root);

    osa_msg_t *retmsg = osa_msg_new_with_data(msg->header.id, "RET:GetDevices", data, strlen(data));
    osa_msg_set_result(retmsg, OSA_ERR_OK);

    osa_msg_send(ioch, retmsg);

    osa_msg_delete(retmsg);
    cJSON_Delete(root);
}


osa_err_t   sysTestDevice(osa_ioch_t *ioch, osa_msg_t *msg)
{
    cJSON *root = cJSON_Parse((char *)msg->data);
    osa_ret_val_if_fail(root != NULL, OSA_ERR_ERR);

    char *devname= cJSON_GetObjectItem(root, "dev_name")->valuestring;

    ats_bus_t   *devbus = ats_bus_find("dev_bus");
    if (!devbus)
    {
        ats_log_error("device bus not found!\n");
        return OSA_ERR_ERR;
    }

    ats_device_t *dev = ats_device_find(devbus, devname);
    osa_ret_val_if_fail(dev != NULL, OSA_ERR_ERR);

    if (!dev->drv)
    {
        ats_log_error("Device(%s) has no test driver, I don't known how to test !\n", dev->name);
        return OSA_ERR_ERR;
    }
    
    osa_sockaddr_t *client_addr=&((osa_socket_t *)(ioch->priv))->addr.in_addr;
    
    ats_report_t *report = ats_report_open((void *)client_addr);
    
    osa_list_t      *l = NULL;
    ats_tevent_t    *node = NULL;
    
    for (l = dev->drv->tevent_list_head.next; 
        l != &dev->drv->tevent_list_head; l = l->next)
    {
        node = osa_list_entry(l, ats_tevent_t, list);
        node->report = report;
    }
    
    ats_test_device_test(dev);
    
    ats_report_close(report);
}


osa_err_t   sysLoginDevice(osa_ioch_t *ioch, osa_msg_t *msg)
{
    ats_log_info("Login device !\n");

    ats_bus_t *devbus = ats_bus_find("dev_bus");
    if (!devbus)
    {
        ats_log_error("no device bus found!\n");
        return OSA_ERR_ERR;
    }
    
    cJSON *root = cJSON_Parse((char *)msg->data);
    osa_ret_val_if_fail(root != NULL, OSA_ERR_ERR);

    char *devName = cJSON_GetObjectItem(root, "dev_name")->valuestring;
    char *user = cJSON_GetObjectItem(root, "user")->valuestring;
    char *passwd = cJSON_GetObjectItem(root, "password")->valuestring;

    ats_device_t *dev = ats_device_find(devbus, devName);
    osa_ret_val_if_fail(dev != NULL, OSA_ERR_ERR);

    osa_err_t flag = OSA_ERR_ERR;

    if (!strcmp(dev->info.user, user) && !strcmp(dev->info.passwd, passwd))
    {
        ats_log_info("Device login successed!\n");

        flag = OSA_ERR_OK;
    }

    osa_msg_t *retmsg = osa_msg_new_with_data(msg->header.id, "RET:LoginDevice", NULL, 0);
    osa_msg_set_result(retmsg, flag);

    osa_msg_send(ioch, retmsg);

    osa_msg_delete(retmsg);
    cJSON_Delete(root);

    return OSA_ERR_OK;
}
