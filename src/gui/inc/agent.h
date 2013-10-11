/**
 *  agent.h
 *
 */


#ifndef __AGENT_H__
#define __AGENT_H__

#include "osa.h"

namespace ATS
{

class Agent
{
public:
    Agent();
    ~Agent();
    void initAgentIOCH();

    osa_err_t   openSocket();
    osa_err_t   closeSocket();
    /** 连接到服务器 */
    osa_err_t   connectToServer(osa_sockaddr_t *serverAddr);
    /** 断开连接 */
    osa_err_t   disconnectFromServer();
    /** 登陆系统 */
    osa_err_t   loginSystem(osa_char_t *user, osa_char_t *passwd);
    /** 退出系统 */
    osa_err_t   exitSystem();

    /** 获取系统设备 */
    osa_err_t   getDevices();
    /** 测试设备 */
    osa_err_t   testDevice(const osa_char_t *devName);
    /** 设置是否自动测试 */
    osa_err_t   setAutoTest(osa_bool_t  bflag);


    osa_err_t   loginDevice(const osa_char_t *devName, const osa_char_t *user, const osa_char_t *passwd);

    osa_bool_t  getLoginState();
    void        setLoginState(osa_bool_t flag);


public:
    osa_ioch_t      ioch;
    osa_socket_t    *socket;

private:

    osa_bool_t      logined;
};

}


extern ATS::Agent *sysAgent;

#endif
