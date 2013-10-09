/**
 *  sdk.h
 *
 */


#ifndef __SDK_LAYER_H__
#define __SDK_LAYER_H__


#include "osa.h"

#ifdef __cplusplus
extern "C"
{
#endif


typedef struct _COMPANY_SDK
{
    osa_char_t      *nameSpace;
    osa_char_t      *info;
    osa_uint32_t    version;

    osa_list_t      list;

    osa_err_t       (*SDK_Init)(void);
    void            (*SDK_Exit)(void);


    /**
     *  Login Device
     *
     *  @param ip ip address
     *  @param port port
     *  @param user user name
     *  @param passwd password for user
     *
     *  @return error code
     */
    osa_err_t       (*SDK_LoginDevice)(osa_char_t *ip, osa_uint32_t port, osa_char_t *user, osa_char_t *passwd);

    /**
     *  Play Live Media
     *
     *  @param playNum  the number for playing
     *  @param chNum the channel for playing
     *  @param priv private data
     *
     *  @return error code
     */
    osa_err_t       (*SDK_PlayLiveMedia)(osa_uint32_t playNum, osa_uint32_t chNum, void *priv);


} SDK_Layer;



// 获取SDK插件对象
SDK_Layer   *SDK_PluginGet();



#ifdef __cplusplus
}
#endif


#endif