#pragma once
#include "afxwin.h"


// Dlg_LVQ 대화 상자입니다.

class Dlg_LVQ : public CDialogEx
{
	DECLARE_DYNAMIC(Dlg_LVQ)

public:
	Dlg_LVQ(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~Dlg_LVQ();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG2 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	CEdit m_edit;
	afx_msg void OnBnClickedOk();
	CString m_edit_val;
};
