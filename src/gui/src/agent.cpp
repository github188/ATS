/**
 *  agent.c
 *
 */


#include "agent.h"
#include "osa.h"
#include "cJSON.h"
#include "log.h"
#include "device.h"

using namespace ATS;

// agent
Agent *sysAgent = NULL;


osa_err_t agentIOChOpen(osa_ioch_t *self, void *param)
{
    osa_socket_t *sock = (osa_socket_t *)param;

    self->iofd = sock->fd;
    self->priv = (void *)sock;

    return OSA_ERR_OK;
}

osa_err_t agentIOChClose(osa_ioch_t *self)
{
    self->iofd = -1;
    self->priv = NULL;

    return OSA_ERR_OK;
}

osa_size_t agentIOChRead(osa_ioch_t *self, osa_char_t *out_data, osa_size_t size)
{
    return osa_tcpclient_read((osa_socket_t *)self->priv, out_data, size);
}

osa_size_t agentIOChWrite(osa_ioch_t *self, osa_char_t *data, osa_size_t size)
{
    return osa_tcpclient_write((osa_socket_t *)self->priv, data, size);
}


Agent::Agent()
{
    logined = OSA_FALSE;

    openSocket();
}

Agent::~Agent()
{
    closeSocket();
    logined = OSA_FALSE;
}


void Agent::initAgentIOCH()
{
    ioch.open = agentIOChOpen;
    ioch.close = agentIOChClose;
    ioch.write = agentIOChWrite;
    ioch.read = agentIOChRead;
}

osa_err_t Agent::openSocket()
{
    socket = osa_tcpclient_open();
    if (!socket)
    {
        GUI_LogError("Failed to open agent socket!\n");
        return OSA_ERR_ERR;
    }

    return OSA_ERR_OK;
}

osa_err_t Agent::closeSocket()
{
    if (socket)
    {
        osa_tcpclient_close(socket);
        socket = NULL;
    }

    setLoginState(false);
    ioch.close(&ioch);

    return OSA_ERR_OK;
}

osa_err_t Agent::connectToServer(osa_sockaddr_t *serverAddr)
{
    if (!socket)
    {
        GUI_LogError("Please open socket at first!\n");
        return OSA_ERR_ERR;
    }

    if (osa_tcpclient_connect(socket, serverAddr) != OSA_ERR_OK)
    {
        GUI_LogError("Failed to connect to server!\n");
        return OSA_ERR_ERR;
    }

    return OSA_ERR_OK;
}


void Agent::setLoginState(osa_bool_t flag)
{
    this->logined = flag;
}


osa_bool_t Agent::getLoginState()
{
    return logined;
}

osa_err_t Agent::disconnectFromServer()
{
    if (socket)
    {
        osa_tcpclient_close(socket);
    }

    return OSA_ERR_OK;
}

osa_err_t Agent::loginSystem(osa_char_t *user, osa_char_t *passwd)
{
    osa_assert(user != NULL);
    osa_assert(passwd != NULL);

    cJSON *root = cJSON_CreateObject();
    cJSON_AddStringToObject(root, "user", user);
    cJSON_AddStringToObject(root, "password", passwd);

    osa_char_t *jsonData =cJSON_Print(root);

    osa_msg_t *sendMsg =osa_msg_new();
    osa_uint32_t msgid = osa_rand_int32(100, 1000);

    osa_msg_init(sendMsg, msgid, "LoginSystem", jsonData, strlen(jsonData));

    osa_msg_t recvMsg;

    ioch.open(&ioch, socket);

    if (osa_msg_send_recv(&ioch, sendMsg, &recvMsg, 2) != OSA_ERR_OK)
    {
        goto err;
    }
    osa_msg_dump(&recvMsg);
    ioch.close(&ioch);
    osa_msg_delete(sendMsg);
    osa_msg_fini(&recvMsg);

    return recvMsg.header.result;

err:
    ioch.close(&ioch);
    osa_msg_delete(sendMsg);
    return OSA_ERR_ERR;
}


osa_err_t Agent::exitSystem()
{
    if (this->logined == OSA_FALSE)
    {
        return OSA_ERR_OK;
    }

    osa_msg_t *sendmsg = osa_msg_new_with_data(100, "ExitSystem", NULL, 0);

    ioch.open(&ioch, (void *)this->socket);

    osa_msg_send(&ioch, sendmsg);

    ioch.close(&ioch);

    osa_msg_delete(sendmsg);

    return OSA_ERR_OK;
}

osa_err_t Agent::getDevices()
{
    osa_msg_t *sendMsg =osa_msg_new_with_data(100, "GetDevices", NULL, 0);

    osa_msg_t recvMsg;

    ioch.open(&ioch, socket);

    if (osa_msg_send_recv(&ioch, sendMsg, &recvMsg, 2) != OSA_ERR_OK)
    {
        ioch.close(&ioch);
        osa_msg_delete(sendMsg);
        osa_msg_fini(&recvMsg);
        return OSA_ERR_ERR;
    }

    osa_uint32_t devNum = 0;
    osa_char_t  *devName = NULL;
    osa_char_t  *devIp = NULL;
    osa_uint32_t devPort = 0;

    cJSON *root = cJSON_Parse((char*)recvMsg.data);

    devNum = cJSON_GetObjectItem(root, "dev_num")->valueint;

    cJSON *devArray = cJSON_GetObjectItem(root, "devs");

    cJSON *dev = devArray->child;

    int i;
    for (i=0; i<devNum; i++)
    {
        devName =cJSON_GetObjectItem(dev, "name")->valuestring;
        devIp = cJSON_GetObjectItem(dev, "ip")->valuestring;
        devPort = cJSON_GetObjectItem(dev, "port")->valueint;

        Device *newDev = new Device(string(devName), string(devIp), devPort);

        newDev->setSdkNameSpace(string("XiongMai_SDK"));
        Device::registerDev(newDev);

        dev = dev->next;
    }

    osa_msg_delete(sendMsg);
    osa_msg_fini(&recvMsg);
    cJSON_Delete(root);

    ioch.close(&ioch);

    return recvMsg.header.result;
}


osa_err_t Agent::testDevice(const osa_char_t *devName)
{

    if (!devName)
        return OSA_ERR_ERR;

    Device *dev = Device::findDev(string(devName));
    if (!dev)
    {
        return OSA_ERR_ERR;
    }

    if (dev->getLoginState() == OSA_FALSE)
    {
        return OSA_ERR_ERR;
    }

    cJSON *root = cJSON_CreateObject();
    cJSON_AddStringToObject(root, "dev_name", devName);

    char *pData = cJSON_Print(root);

    osa_msg_t *sndmsg = osa_msg_new_with_data(200, "TestDevice", pData, strlen(pData));

    ioch.open(&ioch, socket);

    osa_msg_send(&ioch, sndmsg);

    ioch.close(&ioch);

    osa_msg_delete(sndmsg);
    cJSON_Delete(root);

    return OSA_ERR_OK;
}


osa_err_t Agent::loginDevice(const osa_char_t *devName, const osa_char_t *user, const osa_char_t *passwd)
{
    osa_assert(devName != NULL);
    osa_assert(user != NULL);

    cJSON *root = cJSON_CreateObject();
    cJSON_AddStringToObject(root, "dev_name", devName);
    cJSON_AddStringToObject(root, "user", user);
    cJSON_AddStringToObject(root, "password", passwd);

    char *pData = cJSON_Print(root);

    osa_msg_t *sndmsg = osa_msg_new_with_data(200, "LoginDevice", pData, strlen(pData));

    osa_msg_t retmsg;

    ioch.open(&ioch, socket);

    osa_msg_send_recv(&ioch, sndmsg, &retmsg, 2);

    ioch.close(&ioch);

    osa_msg_delete(sndmsg);
    osa_msg_fini(&retmsg);
    cJSON_Delete(root);

    return retmsg.header.result;
}
