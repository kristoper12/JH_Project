
// MFC_SDI_PREPROCESS.h : MFC_SDI_PREPROCESS ���� ���α׷��� ���� �� ��� ����
//
#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"       // �� ��ȣ�Դϴ�.


// CMFC_SDI_PREPROCESSApp:
// �� Ŭ������ ������ ���ؼ��� MFC_SDI_PREPROCESS.cpp�� �����Ͻʽÿ�.
//

class CMFC_SDI_PREPROCESSApp : public CWinApp
{
public:
	CMFC_SDI_PREPROCESSApp();


// �������Դϴ�.
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// �����Դϴ�.
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CMFC_SDI_PREPROCESSApp theApp;
