#ifndef DEVICE_H
#define DEVICE_H

#include <iostream>
#include <string>
#include <list>

#include "osa.h"
#include "sdk_layer.h"

using namespace std;


namespace ATS
{

class DeviceInfo
{
public:
    string          ipAddr;          // IP地址
    osa_uint32_t    port;      // 端口
    string          loginUser;       // 登陆用户
    string          loginPasswd;     // 登陆密码
};


class Device
{
public:
    Device();
    explicit Device(const string &name, const string &ip, osa_uint32_t port);


/** business functions */
public:
    osa_err_t   loginDev(const string &user, const string &password);
    osa_err_t   logoutDev();

    DeviceInfo  getDevInfo();
    string      getDevName();

    osa_bool_t  getLoginState();
    void        setLoginState(osa_bool_t flag);

    osa_err_t   playMedia();

/** other functions */
public:
    static Device *findDev(const string &devName);
    static osa_err_t registerDev(Device *dev);
    static osa_err_t unregisterDev(string &devName);
    static void removeAllDev();

    void setSdkNameSpace(const string &np);
    string getSdkNameSpace();

public:
    static list <Device *>  devList;    // 设备链表

private:
    string      name;                   // 设备名称
    DeviceInfo  devInfo;                // 设备其他信息
    osa_bool_t  logined;                // 是否已经登陆
    string      sdkNameSpace;           // 设备所属的SDK名字空间
    SDK_Layer   *sdk;                   // 设备SDK
    SDK_MediaFD mfd;                    // 流媒体FD
};

}


#endif // DEVICE_H
