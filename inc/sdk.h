/**
 *  sdk.h
 *
 */


#ifndef __SDK_H__
#define __SDK_H__


#include "osa.h"
#include "class.h"


#ifdef __cplusplus
extern "C"
{
#endif

// media fd
typedef		    osa_int32_t	    sdk_mfd_t;

struct ATS_SDK_CLASS
{
    /**
     *  Initialize SDK
     */
    osa_err_t       (*SDK_init)(void);

    /**
     *  Finalize SDK
     */
    void            (*SDK_exit)(void);

    /**
     *  Device match with SDK
     *
     *  @param self sdk
     *  @param dev_name the name of device
     *
     *  @return if device matched with sdk ,return OSA_TRUE , or return OSA_FALSE
     */
    osa_bool_t      (*SDK_match_dev)(ats_sdk_t *self, const osa_char_t *dev_name);

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
    osa_err_t       (*SDK_login_device)(const osa_char_t *ip, osa_uint32_t port,
                                        const osa_char_t *user, const osa_char_t *passwd);

    /**
     *  Play Live Media
     *
     *  @param play_num  the number for playing
     *  @param channel_num the channel for playing
     *  @param user_data user data
     *
     *  @return error code
     */
    sdk_mfd_t       (*SDK_play_live_media)(osa_uint32_t play_num, osa_uint32_t channel_num, void *user_data);

    osa_err_t       (*SDK_stop_live_media)(sdk_mfd_t mfd);

    /** private */
    ats_device_t    *dev;
    osa_char_t      *info;
    osa_uint32_t    version;
    osa_list_t      list;
};



ats_sdk_t   *ats_sdk_plugin_load(const osa_char_t *plugin_file);
void        ats_sdk_plugin_unload(ats_sdk_t *sdk);


#ifdef __cplusplus
}
#endif


#endif
