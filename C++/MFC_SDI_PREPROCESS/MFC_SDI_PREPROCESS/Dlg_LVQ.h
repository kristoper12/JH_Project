#pragma once
#include "afxwin.h"


// Dlg_LVQ ��ȭ �����Դϴ�.

class Dlg_LVQ : public CDialogEx
{
	DECLARE_DYNAMIC(Dlg_LVQ)

public:
	Dlg_LVQ(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~Dlg_LVQ();

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG2 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	CEdit m_edit;
	afx_msg void OnBnClickedOk();
	CString m_edit_val;
};
