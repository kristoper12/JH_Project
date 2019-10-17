
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
};

#ifndef _DEBUG  // MFC_SDI_PREPROCESSView.cpp�� ����� ����
inline CMFC_SDI_PREPROCESSDoc* CMFC_SDI_PREPROCESSView::GetDocument() const
   { return reinterpret_cast<CMFC_SDI_PREPROCESSDoc*>(m_pDocument); }
#endif

