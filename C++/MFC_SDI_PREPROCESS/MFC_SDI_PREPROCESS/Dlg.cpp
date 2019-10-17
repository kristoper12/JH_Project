// Dlg.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "MFC_SDI_PREPROCESS.h"
#include "Dlg.h"
#include "afxdialogex.h"


// Dlg ��ȭ �����Դϴ�.

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


// Dlg �޽��� ó�����Դϴ�.



void Dlg::OnNMCustomdrawSlider1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	*pResult = 0;
	m_hslider_val = m_hslider.GetPos();

	str.Format(_T("%d"), m_hslider_val);
	m_edit.SetWindowTextW(str);
}


BOOL Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
	m_hslider.SetRange(0, 255);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // ����: OCX �Ӽ� �������� FALSE�� ��ȯ�ؾ� �մϴ�.
}
