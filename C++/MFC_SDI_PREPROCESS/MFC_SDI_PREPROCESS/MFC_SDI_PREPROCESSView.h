
// MFC_SDI_PREPROCESSView.h : CMFC_SDI_PREPROCESSView 클래스의 인터페이스
//

#pragma once

class CMFC_SDI_PREPROCESSView : public CView
{
protected: // serialization에서만 만들어집니다.
	CMFC_SDI_PREPROCESSView();
	DECLARE_DYNCREATE(CMFC_SDI_PREPROCESSView)

// 특성입니다.
public:
	CMFC_SDI_PREPROCESSDoc* GetDocument() const;

// 작업입니다.
public:
// 재정의입니다.
public:
	virtual void OnDraw(CDC* pDC);  // 이 뷰를 그리기 위해 재정의되었습니다.
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 구현입니다.
public:
	virtual ~CMFC_SDI_PREPROCESSView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 생성된 메시지 맵 함수
protected:
	DECLARE_MESSAGE_MAP()
public:
};

#ifndef _DEBUG  // MFC_SDI_PREPROCESSView.cpp의 디버그 버전
inline CMFC_SDI_PREPROCESSDoc* CMFC_SDI_PREPROCESSView::GetDocument() const
   { return reinterpret_cast<CMFC_SDI_PREPROCESSDoc*>(m_pDocument); }
#endif

