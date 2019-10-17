
// MFC_SDI_PREPROCESSDoc.h : CMFC_SDI_PREPROCESSDoc 클래스의 인터페이스
//


#pragma once
#include "Dlg.h"


class CMFC_SDI_PREPROCESSDoc : public CDocument
{
protected: // serialization에서만 만들어집니다.
	CMFC_SDI_PREPROCESSDoc();
	DECLARE_DYNCREATE(CMFC_SDI_PREPROCESSDoc)

// 특성입니다.
public:

// 작업입니다.
public:
	Dlg m_dlg;
	CImage m_org_image, m_change_image, m_histogram, m_xprojection, m_yprojection;
	CString m_filepath, str;
	unsigned int m_fileindex, m_size, m_data_offset;
	unsigned int m_img_height, m_img_width, m_widthstep, m_threshold, m_max;
	BYTE **m_red, **m_green, **m_blue, **m_gray, **m_binary;
	BYTE **m_sobel, **m_gaussian, **m_equal, **m_stretch;
	unsigned int *m_xpro, *m_ypro;
	unsigned int m_his[256];
	void CFileInit(unsigned int a_filterindex);
	void GetThresHold();
	void LetProjection(unsigned int *ap_pro, int a_flag);
// 재정의입니다.
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// 구현입니다.
public:
	virtual ~CMFC_SDI_PREPROCESSDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 생성된 메시지 맵 함수
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// 검색 처리기에 대한 검색 콘텐츠를 설정하는 도우미 함수
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
public:
	afx_msg void OnFileopen();
	afx_msg void OnFilesave();
	afx_msg void OnGray();
	afx_msg void OnBinary();
	afx_msg void OnThreshold();
	bool m_isfileopen;
	bool m_isgray;
	bool m_isbinary;
	afx_msg void OnSobel();
	afx_msg void OnGaussian();
	afx_msg void OnEqualization();
	afx_msg void OnStretching();
	bool m_isEqual;
	bool m_isStret;
};