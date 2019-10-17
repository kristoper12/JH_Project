
// MFC_SDI_PREPROCESSView.h : CMFC_SDI_PREPROCESSView Ŭ������ �������̽�
//

#pragma once

class CMFC_SDI_PREPROCESSView : public CView
{
protected: // serialization������ ��������ϴ�.
	CMFC_SDI_PREPROCESSView();
	DECLARE_DYNCREATE(CMFC_SDI_PREPROCESSView)

// Ư���Դϴ�.
public:
	CMFC_SDI_PREPROCESSDoc* GetDocument() const;

// �۾��Դϴ�.
	int m_x;
	int m_y;
	int m_xPos;
	int m_yPos;
	int m_old_xPos;
	int m_old_yPos;
	int m_select_height_rate;
	int m_select_width_rate;
	CImage m_select_image;
	bool m_isclicked;
public:
// �������Դϴ�.
public:
	virtual void OnDraw(CDC* pDC);  // �� �並 �׸��� ���� �����ǵǾ����ϴ�.
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// �����Դϴ�.
public:
	virtual ~CMFC_SDI_PREPROCESSView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ������ �޽��� �� �Լ�
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	bool m_mouseup;
	virtual void OnInitialUpdate();
};

#ifndef _DEBUG  // MFC_SDI_PREPROCESSView.cpp�� ����� ����
inline CMFC_SDI_PREPROCESSDoc* CMFC_SDI_PREPROCESSView::GetDocument() const
   { return reinterpret_cast<CMFC_SDI_PREPROCESSDoc*>(m_pDocument); }
#endif

