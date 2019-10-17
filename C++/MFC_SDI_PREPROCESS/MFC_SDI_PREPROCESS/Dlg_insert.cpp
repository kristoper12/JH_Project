// Dlg_insert.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "MFC_SDI_PREPROCESS.h"
#include "Dlg_insert.h"
#include "afxdialogex.h"
#include "Dlg_List.h"


// Dlg_insert ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(Dlg_insert, CDialogEx)

Dlg_insert::Dlg_insert(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG5, pParent)
	, m_insert_Alpha(_T(""))
	, m_insert_Radius(_T(""))
{

}

Dlg_insert::~Dlg_insert()
{
}

void Dlg_insert::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_insert_Alpha);
	DDX_Text(pDX, IDC_EDIT3, m_insert_Radius);
}


BEGIN_MESSAGE_MAP(Dlg_insert, CDialogEx)
	ON_BN_CLICKED(IDOK, &Dlg_insert::OnBnClickedOk)
END_MESSAGE_MAP()


// Dlg_insert �޽��� ó�����Դϴ�.


void Dlg_insert::OnBnClickedOk()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	CDialogEx::OnOK();
	m_dlg->m_Alpha = _wtoi(m_insert_Alpha);
	m_dlg->m_Radius = _wtoi(m_insert_Radius);
}
