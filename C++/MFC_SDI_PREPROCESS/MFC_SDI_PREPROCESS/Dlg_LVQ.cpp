// Dlg_LVQ.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "MFC_SDI_PREPROCESS.h"
#include "Dlg_LVQ.h"
#include "afxdialogex.h"


// Dlg_LVQ ��ȭ �����Դϴ�.

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


// Dlg_LVQ �޽��� ó�����Դϴ�.


void Dlg_LVQ::OnBnClickedOk()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	CDialogEx::OnOK();
	/*GetDlgItemText(m_ReferenceVector, m_ReferenceVector_val, 3);*/
}
