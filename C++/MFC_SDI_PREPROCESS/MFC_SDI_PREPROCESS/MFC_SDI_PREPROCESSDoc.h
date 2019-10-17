
// MFC_SDI_PREPROCESSDoc.h : CMFC_SDI_PREPROCESSDoc Ŭ������ �������̽�
//


#pragma once
#include "Dlg.h"


class CMFC_SDI_PREPROCESSDoc : public CDocument
{
protected: // serialization������ ��������ϴ�.
	CMFC_SDI_PREPROCESSDoc();
	DECLARE_DYNCREATE(CMFC_SDI_PREPROCESSDoc)

// Ư���Դϴ�.
public:

// �۾��Դϴ�.
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
// �������Դϴ�.
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// �����Դϴ�.
public:
	virtual ~CMFC_SDI_PREPROCESSDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ������ �޽��� �� �Լ�
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// �˻� ó���⿡ ���� �˻� �������� �����ϴ� ����� �Լ�
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