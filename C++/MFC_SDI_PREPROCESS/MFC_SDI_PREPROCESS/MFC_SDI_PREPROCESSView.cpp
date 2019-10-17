
// MFC_SDI_PREPROCESSView.cpp : CMFC_SDI_PREPROCESSView Ŭ������ ����
//

#include "stdafx.h"
// SHARED_HANDLERS�� �̸� ����, ����� �׸� �� �˻� ���� ó���⸦ �����ϴ� ATL ������Ʈ���� ������ �� ������
// �ش� ������Ʈ�� ���� �ڵ带 �����ϵ��� �� �ݴϴ�.
#ifndef SHARED_HANDLERS
#include "MFC_SDI_PREPROCESS.h"
#endif

#include "MFC_SDI_PREPROCESSDoc.h"
#include "MFC_SDI_PREPROCESSView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMFC_SDI_PREPROCESSView

IMPLEMENT_DYNCREATE(CMFC_SDI_PREPROCESSView, CView)

BEGIN_MESSAGE_MAP(CMFC_SDI_PREPROCESSView, CView)
	// ǥ�� �μ� ����Դϴ�.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
END_MESSAGE_MAP()

// CMFC_SDI_PREPROCESSView ����/�Ҹ�

CMFC_SDI_PREPROCESSView::CMFC_SDI_PREPROCESSView()
{
	// TODO: ���⿡ ���� �ڵ带 �߰��մϴ�.

}

CMFC_SDI_PREPROCESSView::~CMFC_SDI_PREPROCESSView()
{
}

BOOL CMFC_SDI_PREPROCESSView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs�� �����Ͽ� ���⿡��
	//  Window Ŭ���� �Ǵ� ��Ÿ���� �����մϴ�.

	return CView::PreCreateWindow(cs);
}

// CMFC_SDI_PREPROCESSView �׸���

void CMFC_SDI_PREPROCESSView::OnDraw(CDC* /*pDC*/)
{
	CMFC_SDI_PREPROCESSDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: ���⿡ ���� �����Ϳ� ���� �׸��� �ڵ带 �߰��մϴ�.
	CDC *dc = GetDC();
	dc->SetStretchBltMode(HALFTONE);	

	Rectangle(dc->m_hDC, 10, 10, 310, 310);
	Rectangle(dc->m_hDC, 320, 10, 620, 310);
	MoveToEx(dc->m_hDC, 30, 620, NULL);
	LineTo(dc->m_hDC, 284, 620);
	Rectangle(dc->m_hDC, 630, 10, 930, 310);
	Rectangle(dc->m_hDC, 320, 320, 620, 620);
	GetDocument();
	if (pDoc->m_isfileopen) {
		pDoc->m_org_image.StretchBlt(dc->m_hDC, 11, 11, 298, 298, SRCCOPY);
		if (pDoc->m_isgray) {
			pDoc->m_change_image.StretchBlt(dc->m_hDC, 321, 11, 298, 298, SRCCOPY);
			pDoc->m_histogram.StretchBlt(dc->m_hDC, 31, 321, 256, 300, SRCCOPY);
			/*HBRUSH hBrush = CreateSolidBrush(RGB(255, 255, 255));
			HBRUSH Old_hBrush = (HBRUSH)SelectObject(dc->m_hDC, hBrush);
			for (int i = 31; i < 288; i++) {
				MoveToEx(dc->m_hDC, i, 321, NULL);
				LineTo(dc->m_hDC, i, 621 - pDoc->m_his[i - 31]);
			}
			SelectObject(dc->m_hDC, Old_hBrush);*/
		}
		if (pDoc->m_isbinary) {
			pDoc->m_change_image.StretchBlt(dc->m_hDC, 321, 11, 298, 298, SRCCOPY);
			pDoc->m_xprojection.StretchBlt(dc->m_hDC, 631, 11, 298, 298, SRCCOPY);
			pDoc->m_yprojection.StretchBlt(dc->m_hDC, 321, 321, 298, 298, SRCCOPY);
		}
	}
	ReleaseDC(dc);
}


// CMFC_SDI_PREPROCESSView �μ�

BOOL CMFC_SDI_PREPROCESSView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// �⺻���� �غ�
	return DoPreparePrinting(pInfo);
}

void CMFC_SDI_PREPROCESSView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: �μ��ϱ� ���� �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
}

void CMFC_SDI_PREPROCESSView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: �μ� �� ���� �۾��� �߰��մϴ�.
}


// CMFC_SDI_PREPROCESSView ����

#ifdef _DEBUG
void CMFC_SDI_PREPROCESSView::AssertValid() const
{
	CView::AssertValid();
}

void CMFC_SDI_PREPROCESSView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMFC_SDI_PREPROCESSDoc* CMFC_SDI_PREPROCESSView::GetDocument() const // ����׵��� ���� ������ �ζ������� �����˴ϴ�.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMFC_SDI_PREPROCESSDoc)));
	return (CMFC_SDI_PREPROCESSDoc*)m_pDocument;
}
#endif //_DEBUG


// CMFC_SDI_PREPROCESSView �޽��� ó����