// Dlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "MFC_SDI_PREPROCESS.h"
#include "Dlg.h"
#include "afxdialogex.h"


// Dlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(Dlg, CDialogEx)

Dlg::Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG1, pParent)
	, m_hslider_val(0)
	, m_edit_val(_T(""))
{

}

Dlg::~Dlg()
{
}

void Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_SLIDER1, m_hslider);
	DDX_Slider(pDX, IDC_SLIDER1, m_hslider_val);
	DDX_Control(pDX, IDC_EDIT1, m_edit);
	DDX_Text(pDX, IDC_EDIT1, m_edit_val);
}


BEGIN_MESSAGE_MAP(Dlg, CDialogEx)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER1, &Dlg::OnNMCustomdrawSlider1)
END_MESSAGE_MAP()


// Dlg 메시지 처리기입니다.



void Dlg::OnNMCustomdrawSlider1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	*pResult = 0;
	m_hslider_val = m_hslider.GetPos();

	str.Format(_T("%d"), m_hslider_val);
	m_edit.SetWindowTextW(str);
}


BOOL Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	m_hslider.SetRange(0, 255);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}
