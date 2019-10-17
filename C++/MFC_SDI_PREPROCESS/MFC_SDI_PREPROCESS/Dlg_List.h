#pragma once
#include "afxcmn.h"
#include "Dlg_insert.h"

// Dlg_List 대화 상자입니다.

class Dlg_List : public CDialogEx
{
	DECLARE_DYNAMIC(Dlg_List)

public:
	Dlg_List(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~Dlg_List();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG4 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	Dlg_insert m_dlginsert;
	CListCtrl m_listinfo;
	virtual BOOL OnInitDialog();
	int m_Alpha;
	int m_Radius;
};
