#ifndef CONF_MOD_H
#define CONF_MOD_H



#ifdef CONF_MOD_EXPORTS
#define CONF_MOD_API  __declspec(dllexport)
#else
#define CONF_MOD_API  __declspec(dllimport)   //VC 用
#endif


// 参数一:设备信息，二、获取数据类型，三、用户参数.
typedef int (CALLBACK * GetParmBackCallFunc)(long ConfigType, int nChannel,char* pConfigBuf,DWORD dwBufSize, DWORD dwUserParam, DWORD *lpRet);
typedef int (CALLBACK * SaveParmBackCallFunc)(long ConfigType, int nChannel,char* pConfigBuf,DWORD dwBufSize,DWORD dwUserParam);



//初始化
CONF_MOD_API BOOL Config_Init(CWnd *pParent);

//反初始化
CONF_MOD_API BOOL Config_UnInit();


//初始化语言
//pLanguagePath 语言绝对路径，包含文件名
CONF_MOD_API BOOL Config_languageInit(TCHAR *pLanguagePath);


//设备获取数据和保存数据回调
CONF_MOD_API BOOL Config_SetCallback(void * getCalback, void * saveCallback, DWORD dwUser);

//移动窗体位置
CONF_MOD_API BOOL Config_MoveWindow(CRect *rect, BOOL bShow);


//设备更改，重新获取所有数据
CONF_MOD_API BOOL Config_Refush();



#endif