#include "device.h"
#include "agent.h"


using namespace ATS;
using namespace std;


list <Device *> Device::devList;


Device::Device()
{
    name = "dummy";
    devInfo.ipAddr = "0.0.0.0";
    devInfo.port = 2000;
    devInfo.loginUser = "admin";
    devInfo.loginPasswd = "admin";
    logined = OSA_FALSE;
}


Device::Device(const string &name, const string &ip, osa_uint32_t port)
{
    this->name = name;
    this->devInfo.ipAddr = ip;
    this->devInfo.port = port;
    this->devInfo.loginUser="";
    this->devInfo.loginPasswd="";
    this->logined = OSA_FALSE;
    this->mfd = -1;
}


Device *Device::findDev(const string &devName)
{
    list<Device *>::iterator itr;
    Device *dev = NULL;

    for (itr=devList.begin(); itr!=devList.end(); itr++)
    {
        dev = *(itr);
        if (dev->name == devName)
        {
            break;
        }
    }

    if (itr != devList.end())
    {
        return (Device *)(*itr);
    }

    return NULL;
}

osa_err_t Device::registerDev(Device *dev)
{
    if (findDev(dev->name) != NULL)
    {
        osa_log_error("Device exist: %s!\n", dev->name.c_str());
        return OSA_ERR_ERR;
    }

    devList.push_back(dev);

    return OSA_ERR_OK;
}


osa_err_t Device::unregisterDev(string &devName)
{
    Device *dev = NULL;
    list<Device *>::iterator itr;

    for (itr=devList.begin(); itr != devList.end();)
    {
        dev = *itr;
        if (dev->name == devName)
        {
            itr=devList.erase(itr);
            delete(dev);
            break;
        }
        else
        {
            itr++;
        }
    }

    return OSA_ERR_OK;
}

void Device::removeAllDev()
{
    list <Device *>::iterator itr;
    Device *dev = NULL;

    for (itr=devList.begin(); itr != devList.end(); itr++)
    {
        dev = (*itr);
        itr=devList.erase(itr);
        delete dev;
    }
}

void Device::setSdkNameSpace(const string &np)
{
    sdkNameSpace = np;
}


string Device::getSdkNameSpace()
{
    return sdkNameSpace;
}

osa_err_t Device::loginDev(const string &user, const string &password)
{
    devInfo.loginUser=user;
    devInfo.loginPasswd = password;

    return sysAgent->loginDevice(name.c_str(), user.c_str(), password.c_str());
}

string Device::getDevName()
{
    return this->name;
}

DeviceInfo Device::getDevInfo()
{
    return this->devInfo;
}


osa_bool_t Device::getLoginState()
{
    return logined;
}

void Device::setLoginState(osa_bool_t flag)
{
    logined = flag;
}

osa_err_t Device::playMedia()
{
    if (logined != OSA_TRUE)
    {
        return OSA_ERR_ERR;
    }
    return OSA_ERR_OK;
}

