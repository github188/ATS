// xm_sdk.h : xm_sdk DLL ����ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// Cxm_sdkApp
// �йش���ʵ�ֵ���Ϣ������� xm_sdk.cpp
//

class Cxm_sdkApp : public CWinApp
{
public:
    Cxm_sdkApp();

// ��д
public:
    virtual BOOL InitInstance();

    DECLARE_MESSAGE_MAP()
};
