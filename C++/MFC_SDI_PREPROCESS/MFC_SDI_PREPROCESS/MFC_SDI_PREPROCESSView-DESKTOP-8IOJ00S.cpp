
// MFC_SDI_PREPROCESSView.cpp : CMFC_SDI_PREPROCESSView 클래스의 구현
//

#include "stdafx.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
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
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
END_MESSAGE_MAP()

// CMFC_SDI_PREPROCESSView 생성/소멸

CMFC_SDI_PREPROCESSView::CMFC_SDI_PREPROCESSView()
	: m_mouseup(false)
{
	// TODO: 여기에 생성 코드를 추가합니다.
	m_isclicked = false;
}

CMFC_SDI_PREPROCESSView::~CMFC_SDI_PREPROCESSView()
{
}

BOOL CMFC_SDI_PREPROCESSView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CView::PreCreateWindow(cs);
}

// CMFC_SDI_PREPROCESSView 그리기

void CMFC_SDI_PREPROCESSView::OnDraw(CDC* /*pDC*/)
{
	CMFC_SDI_PREPROCESSDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.
	CDC *dc = GetDC();
	dc->SetStretchBltMode(HALFTONE);
	HBRUSH hbrush = (HBRUSH)GetStockObject(NULL_BRUSH);
	HPEN hpen = CreatePen(PS_SOLID, 3, RGB(0, 255, 0));
	HPEN old_hpen;
	HBRUSH old_hbrush;

	old_hbrush = (HBRUSH)SelectObject(dc->m_hDC, hbrush);

	Rectangle(dc->m_hDC, 10, 10, 310, 310);
	Rectangle(dc->m_hDC, 320, 10, 620, 310);
	MoveToEx(dc->m_hDC, 30, 620, NULL);
	LineTo(dc->m_hDC, 284, 620);
	Rectangle(dc->m_hDC, 630, 10, 930, 310);
	Rectangle(dc->m_hDC, 320, 320, 620, 620);
	Rectangle(dc->m_hDC, 630, 320, 930, 620);
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
		if (pDoc->m_isLVQ) {
			pDoc->m_change_image.StretchBlt(dc->m_hDC, 321, 11, 298, 298, SRCCOPY);
		}
		if (pDoc->m_isselect) {
			if (m_mouseup) {
				m_select_image.StretchBlt(dc->m_hDC, 631, 321, 298, 298, SRCCOPY);
			}
		}
		old_hpen = (HPEN)SelectObject(dc->m_hDC, hpen);

		Rectangle(dc->m_hDC, m_xPos, m_yPos, m_old_xPos, m_old_yPos);

		SelectObject(dc->m_hDC, old_hpen);
		DeleteObject(hpen);
		DeleteObject(old_hpen);
	}

	SelectObject(dc->m_hDC, old_hbrush);
	DeleteObject(hbrush);
	DeleteObject(old_hbrush);

	ReleaseDC(dc);
}


// CMFC_SDI_PREPROCESSView 인쇄

BOOL CMFC_SDI_PREPROCESSView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void CMFC_SDI_PREPROCESSView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void CMFC_SDI_PREPROCESSView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}


// CMFC_SDI_PREPROCESSView 진단

#ifdef _DEBUG
void CMFC_SDI_PREPROCESSView::AssertValid() const
{
	CView::AssertValid();
}

void CMFC_SDI_PREPROCESSView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMFC_SDI_PREPROCESSDoc* CMFC_SDI_PREPROCESSView::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMFC_SDI_PREPROCESSDoc)));
	return (CMFC_SDI_PREPROCESSDoc*)m_pDocument;
}
#endif //_DEBUG


// CMFC_SDI_PREPROCESSView 메시지 처리기

void CMFC_SDI_PREPROCESSView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	CView::OnLButtonDown(nFlags, point);
	
	CMFC_SDI_PREPROCESSDoc* pDoc = GetDocument();

	if (pDoc->m_isfileopen) {
		if (!pDoc->m_isselect) {
			GetCursorPos(&point);
			CDC *dc = GetDC();
			CClientDC hdc(this);
			
			pDoc->m_rgb = GetPixel(GetDesktopWindow()->GetDC()->GetSafeHdc(), point.x, point.y);

			HBRUSH hBrush = CreateSolidBrush(pDoc->m_rgb);
			HBRUSH Old_hBrush = (HBRUSH)SelectObject(dc->m_hDC, hBrush);

			Rectangle(dc->m_hDC, 630, 320, 930, 370);

			SelectObject(dc->m_hDC, Old_hBrush);
			DeleteObject(hBrush);
			ReleaseDC(dc);
		}
		else if (pDoc->m_isselect) {
			m_mouseup = false;
			m_old_xPos = point.x;
			m_old_yPos = point.y;
			m_isclicked = true;
		}
	}
}
void CMFC_SDI_PREPROCESSView::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	CView::OnLButtonUp(nFlags, point);
	
	m_isclicked = false;

	CMFC_SDI_PREPROCESSDoc* pDoc = GetDocument();
	if (pDoc->m_isselect) {
		m_mouseup = true;
		m_select_width_rate = (int)(((float)pDoc->m_img_width * (float)(m_xPos - m_old_xPos)) / 298.0);
		m_select_height_rate = (int)(((float)pDoc->m_img_height * (float)(m_yPos - m_old_yPos)) / 298.0);
		m_x = (int)(((float)m_old_xPos * (float)pDoc->m_img_width) / 298.0);
		m_y = (int)(((float)m_old_yPos * (float)pDoc->m_img_height) / 298.0);

		if (m_select_image != NULL) {
			m_select_image.Destroy();
		}
		m_select_image.Create(m_select_width_rate, m_select_height_rate, pDoc->m_img_bit);

		for (int i = m_y; i < m_select_height_rate + m_y; i++) {
			for (int j = m_x; j < m_select_width_rate + m_x; j++) {
				m_select_image.SetPixel(j - m_x, i - m_y, RGB(pDoc->m_red[i][j], pDoc->m_green[i][j], pDoc->m_blue[i][j]));
			}
		}
		Invalidate(NULL);
	}
}
void CMFC_SDI_PREPROCESSView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	CView::OnMouseMove(nFlags, point);

	if (m_isclicked) {
		m_xPos = point.x;
		m_yPos = point.y;

		if (m_xPos > 309)
			m_xPos = 309;
		if (m_xPos < 11)
			m_xPos = 11;
		if (m_yPos > 309)
			m_yPos = 309;
		if (m_yPos < 11)
			m_yPos = 11;
		Invalidate(NULL);
	}

}


void CMFC_SDI_PREPROCESSView::OnInitialUpdate()
{
	CView::OnInitialUpdate();
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
}
