#pragma once
#include "afxcmn.h"
#include "Dlg_insert.h"

// Dlg_List ��ȭ �����Դϴ�.

class Dlg_List : public CDialogEx
{
	DECLARE_DYNAMIC(Dlg_List)

public:
	Dlg_List(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~Dlg_List();

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG4 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	Dlg_insert m_dlginsert;
	CListCtrl m_listinfo;
	virtual BOOL OnInitDialog();
	int m_Alpha;
	int m_Radius;
};
