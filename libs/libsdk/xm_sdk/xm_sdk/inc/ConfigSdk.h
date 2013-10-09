#ifndef CONF_MOD_H
#define CONF_MOD_H



#ifdef CONF_MOD_EXPORTS
#define CONF_MOD_API  __declspec(dllexport)
#else
#define CONF_MOD_API  __declspec(dllimport)   //VC ��
#endif


// ����һ:�豸��Ϣ��������ȡ�������ͣ������û�����.
typedef int (CALLBACK * GetParmBackCallFunc)(long ConfigType, int nChannel,char* pConfigBuf,DWORD dwBufSize, DWORD dwUserParam, DWORD *lpRet);
typedef int (CALLBACK * SaveParmBackCallFunc)(long ConfigType, int nChannel,char* pConfigBuf,DWORD dwBufSize,DWORD dwUserParam);



//��ʼ��
CONF_MOD_API BOOL Config_Init(CWnd *pParent);

//����ʼ��
CONF_MOD_API BOOL Config_UnInit();


//��ʼ������
//pLanguagePath ���Ծ���·���������ļ���
CONF_MOD_API BOOL Config_languageInit(TCHAR *pLanguagePath);


//�豸��ȡ���ݺͱ������ݻص�
CONF_MOD_API BOOL Config_SetCallback(void * getCalback, void * saveCallback, DWORD dwUser);

//�ƶ�����λ��
CONF_MOD_API BOOL Config_MoveWindow(CRect *rect, BOOL bShow);


//�豸���ģ����»�ȡ��������
CONF_MOD_API BOOL Config_Refush();



#endif