#pragma once


// Dlg_insert ��ȭ �����Դϴ�.

class Dlg_insert : public CDialogEx
{
	DECLARE_DYNAMIC(Dlg_insert)

public:
	Dlg_insert(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~Dlg_insert();
	class Dlg_List *m_dlg;

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG5 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	CString m_insert_Alpha;
	CString m_insert_Radius;
	afx_msg void OnBnClickedOk();
};
