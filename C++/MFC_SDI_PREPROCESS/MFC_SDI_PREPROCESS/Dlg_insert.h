#pragma once


// Dlg_insert 대화 상자입니다.

class Dlg_insert : public CDialogEx
{
	DECLARE_DYNAMIC(Dlg_insert)

public:
	Dlg_insert(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~Dlg_insert();
	class Dlg_List *m_dlg;

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG5 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	CString m_insert_Alpha;
	CString m_insert_Radius;
	afx_msg void OnBnClickedOk();
};
