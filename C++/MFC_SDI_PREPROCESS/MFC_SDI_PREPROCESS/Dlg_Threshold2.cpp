// Dlg_Threshold2.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "MFC_SDI_PREPROCESS.h"
#include "Dlg_Threshold2.h"
#include "afxdialogex.h"


// Dlg_Threshold2 대화 상자입니다.

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


// Dlg_Threshold2 메시지 처리기입니다.


BOOL Dlg_Threshold2::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	m_hslider_min.SetRange(0, 255);
	m_hslider_max.SetRange(0, 255);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


void Dlg_Threshold2::OnNMCustomdrawSlider1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	*pResult = 0;
	m_hslider_val_min = m_hslider_min.GetPos();

	str.Format(_T("%d"), m_hslider_val_min);
	m_edit_min.SetWindowTextW(str);
}


void Dlg_Threshold2::OnNMCustomdrawSlider2(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	*pResult = 0;
	m_hslider_val_max = m_hslider_max.GetPos();

	str.Format(_T("%d"), m_hslider_val_max);
	m_edit_max.SetWindowTextW(str);
}
