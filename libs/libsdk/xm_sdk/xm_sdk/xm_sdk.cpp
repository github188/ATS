// xm_sdk.cpp : ���� DLL �ĳ�ʼ�����̡�
//

#include "stdafx.h"
#include "xm_sdk.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

//
//TODO: ����� DLL ����� MFC DLL �Ƕ�̬���ӵģ�
//		��Ӵ� DLL �������κε���
//		MFC �ĺ������뽫 AFX_MANAGE_STATE ����ӵ�
//		�ú�������ǰ�档
//
//		����:
//
//		extern "C" BOOL PASCAL EXPORT ExportedFunction()
//		{
//			AFX_MANAGE_STATE(AfxGetStaticModuleState());
//			// �˴�Ϊ��ͨ������
//		}
//
//		�˺������κ� MFC ����
//		������ÿ��������ʮ����Ҫ������ζ��
//		��������Ϊ�����еĵ�һ�����
//		���֣������������ж������������
//		������Ϊ���ǵĹ��캯���������� MFC
//		DLL ���á�
//
//		�й�������ϸ��Ϣ��
//		����� MFC ����˵�� 33 �� 58��
//

// Cxm_sdkApp

BEGIN_MESSAGE_MAP(Cxm_sdkApp, CWinApp)
END_MESSAGE_MAP()


// Cxm_sdkApp ����

Cxm_sdkApp::Cxm_sdkApp()
{
    // TODO: �ڴ˴���ӹ�����룬
    // ��������Ҫ�ĳ�ʼ�������� InitInstance ��
}


// Ψһ��һ�� Cxm_sdkApp ����

Cxm_sdkApp theApp;


// Cxm_sdkApp ��ʼ��

BOOL Cxm_sdkApp::InitInstance()
{
    CWinApp::InitInstance();

    return TRUE;
}
