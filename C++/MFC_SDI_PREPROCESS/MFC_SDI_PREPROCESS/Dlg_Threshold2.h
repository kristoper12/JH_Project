#pragma once
#include "afxwin.h"
#include "afxcmn.h"


// Dlg_Threshold2 ��ȭ �����Դϴ�.

class Dlg_Threshold2 : public CDialogEx
{
	DECLARE_DYNAMIC(Dlg_Threshold2)

public:
	Dlg_Threshold2(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~Dlg_Threshold2();

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG3 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	CString str;
	CEdit m_edit_min;
	CEdit m_edit_max;
	CSliderCtrl m_hslider_min;
	CSliderCtrl m_hslider_max;
	virtual BOOL OnInitDialog();
	afx_msg void OnNMCustomdrawSlider1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMCustomdrawSlider2(NMHDR *pNMHDR, LRESULT *pResult);
	int m_hslider_val_min;
	int m_hslider_val_max;
};
