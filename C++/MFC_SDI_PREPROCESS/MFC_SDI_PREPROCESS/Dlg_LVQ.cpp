// Dlg_LVQ.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "MFC_SDI_PREPROCESS.h"
#include "Dlg_LVQ.h"
#include "afxdialogex.h"


// Dlg_LVQ 대화 상자입니다.

IMPLEMENT_DYNAMIC(Dlg_LVQ, CDialogEx)

Dlg_LVQ::Dlg_LVQ(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG2, pParent)
	, m_edit_val(_T(""))
{

}

Dlg_LVQ::~Dlg_LVQ()
{
}

void Dlg_LVQ::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, m_edit);
	DDX_Text(pDX, IDC_EDIT1, m_edit_val);
}


BEGIN_MESSAGE_MAP(Dlg_LVQ, CDialogEx)
	ON_BN_CLICKED(IDOK, &Dlg_LVQ::OnBnClickedOk)
END_MESSAGE_MAP()


// Dlg_LVQ 메시지 처리기입니다.


void Dlg_LVQ::OnBnClickedOk()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CDialogEx::OnOK();
	/*GetDlgItemText(m_ReferenceVector, m_ReferenceVector_val, 3);*/
}
