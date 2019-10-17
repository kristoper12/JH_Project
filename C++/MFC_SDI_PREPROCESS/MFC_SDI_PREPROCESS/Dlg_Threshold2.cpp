// Dlg_Threshold2.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "MFC_SDI_PREPROCESS.h"
#include "Dlg_Threshold2.h"
#include "afxdialogex.h"


// Dlg_Threshold2 ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(Dlg_Threshold2, CDialogEx)

Dlg_Threshold2::Dlg_Threshold2(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG3, pParent)
	, m_hslider_val_min(0)
	, m_hslider_val_max(0)
{

}

Dlg_Threshold2::~Dlg_Threshold2()
{
}

void Dlg_Threshold2::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, m_edit_min);
	DDX_Control(pDX, IDC_EDIT2, m_edit_max);
	DDX_Control(pDX, IDC_SLIDER1, m_hslider_min);
	DDX_Control(pDX, IDC_SLIDER2, m_hslider_max);
	DDX_Slider(pDX, IDC_SLIDER1, m_hslider_val_min);
	DDX_Slider(pDX, IDC_SLIDER2, m_hslider_val_max);
}


BEGIN_MESSAGE_MAP(Dlg_Threshold2, CDialogEx)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER1, &Dlg_Threshold2::OnNMCustomdrawSlider1)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER2, &Dlg_Threshold2::OnNMCustomdrawSlider2)
END_MESSAGE_MAP()


// Dlg_Threshold2 �޽��� ó�����Դϴ�.


BOOL Dlg_Threshold2::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
	m_hslider_min.SetRange(0, 255);
	m_hslider_max.SetRange(0, 255);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // ����: OCX �Ӽ� �������� FALSE�� ��ȯ�ؾ� �մϴ�.
}


void Dlg_Threshold2::OnNMCustomdrawSlider1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	*pResult = 0;
	m_hslider_val_min = m_hslider_min.GetPos();

	str.Format(_T("%d"), m_hslider_val_min);
	m_edit_min.SetWindowTextW(str);
}


void Dlg_Threshold2::OnNMCustomdrawSlider2(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	*pResult = 0;
	m_hslider_val_max = m_hslider_max.GetPos();

	str.Format(_T("%d"), m_hslider_val_max);
	m_edit_max.SetWindowTextW(str);
}
