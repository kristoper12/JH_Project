
// MFC_SDI_PREPROCESSDoc.cpp : CMFC_SDI_PREPROCESSDoc 클래스의 구현
//

#include "stdafx.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "MFC_SDI_PREPROCESS.h"
#endif
#include "MainFrm.h"
#include "MFC_SDI_PREPROCESSDoc.h"
#include "MFC_SDI_PREPROCESSView.h"

#include <propkey.h>

#define BRIGHT 70
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMFC_SDI_PREPROCESSDoc

IMPLEMENT_DYNCREATE(CMFC_SDI_PREPROCESSDoc, CDocument)

BEGIN_MESSAGE_MAP(CMFC_SDI_PREPROCESSDoc, CDocument)
	ON_COMMAND(ID_FILEOPEN, &CMFC_SDI_PREPROCESSDoc::OnFileopen)
	ON_COMMAND(ID_FILESAVE, &CMFC_SDI_PREPROCESSDoc::OnFilesave)
	ON_COMMAND(ID_GRAY, &CMFC_SDI_PREPROCESSDoc::OnGray)
	ON_COMMAND(ID_BINARY, &CMFC_SDI_PREPROCESSDoc::OnBinary)
	ON_COMMAND(ID_THRESHOLD, &CMFC_SDI_PREPROCESSDoc::OnThreshold)
	ON_COMMAND(ID_SOBEL, &CMFC_SDI_PREPROCESSDoc::OnSobel)
	ON_COMMAND(ID_GAUSSIAN, &CMFC_SDI_PREPROCESSDoc::OnGaussian)
	ON_COMMAND(ID_EQUALIZATION, &CMFC_SDI_PREPROCESSDoc::OnEqualization)
	ON_COMMAND(ID_STRETCHING, &CMFC_SDI_PREPROCESSDoc::OnStretching)
	ON_COMMAND(ID_LABELING, &CMFC_SDI_PREPROCESSDoc::OnLabeling)
	ON_COMMAND(ID_LVQ, &CMFC_SDI_PREPROCESSDoc::OnLvq)
	ON_COMMAND(ID_THRESHOLD_TWO, &CMFC_SDI_PREPROCESSDoc::OnThresholdTwo)
	ON_COMMAND(ID_SELECT_AREA, &CMFC_SDI_PREPROCESSDoc::OnSelectArea)
	ON_COMMAND(ID_GRAY_SAVE, &CMFC_SDI_PREPROCESSDoc::OnGraySave)
	ON_COMMAND(ID_CENTER_POINT, &CMFC_SDI_PREPROCESSDoc::OnCenterPoint)
END_MESSAGE_MAP()


// CMFC_SDI_PREPROCESSDoc 생성/소멸

CMFC_SDI_PREPROCESSDoc::CMFC_SDI_PREPROCESSDoc()
	: m_isfileopen(false)
	, m_isgray(false)
	, m_isbinary(false)
	, m_isEqual(false)
	, m_isStret(false)
	, m_isLVQ(false)
	, m_ischange(false)
	, m_islabeling(false)
	, m_isselect(false)
{
	// TODO: 여기에 일회성 생성 코드를 추가합니다.

}

CMFC_SDI_PREPROCESSDoc::~CMFC_SDI_PREPROCESSDoc()
{
}

BOOL CMFC_SDI_PREPROCESSDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: 여기에 재초기화 코드를 추가합니다.
	// SDI 문서는 이 문서를 다시 사용합니다.

	return TRUE;
}




// CMFC_SDI_PREPROCESSDoc serialization

void CMFC_SDI_PREPROCESSDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: 여기에 저장 코드를 추가합니다.
	}
	else
	{
		// TODO: 여기에 로딩 코드를 추가합니다.
	}
}

#ifdef SHARED_HANDLERS

// 축소판 그림을 지원합니다.
void CMFC_SDI_PREPROCESSDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// 문서의 데이터를 그리려면 이 코드를 수정하십시오.
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT)GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// 검색 처리기를 지원합니다.
void CMFC_SDI_PREPROCESSDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// 문서의 데이터에서 검색 콘텐츠를 설정합니다.
	// 콘텐츠 부분은 ";"로 구분되어야 합니다.

	// 예: strSearchContent = _T("point;rectangle;circle;ole object;");
	SetSearchContent(strSearchContent);
}

void CMFC_SDI_PREPROCESSDoc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = NULL;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != NULL)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// CMFC_SDI_PREPROCESSDoc 진단

#ifdef _DEBUG
void CMFC_SDI_PREPROCESSDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CMFC_SDI_PREPROCESSDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CMFC_SDI_PREPROCESSDoc 명령
int abs(int x) {
	if (x < 0)
		return x * -1;
	else
		return x;
}
float abs(float x) {
	if (x > 0)
		return x;
	else
		return x * -1;
}

void CMFC_SDI_PREPROCESSDoc::GetThresHold() {
	int sum = 0;
	for (int i = m_img_height - 1; i >= 0; i--) {
		for (int j = 0; j < m_img_width; j++) {
			sum += m_gray[i][j];
		}
	}
	m_threshold = sum / (m_img_height * m_img_width);
}
void CMFC_SDI_PREPROCESSDoc::LetProjection(unsigned int *ap_pro, int a_flag) {

	if (!m_isselect) {
		if (a_flag == 1) {
			for (int i = 0; i < m_img_height; i++) {
				for (int j = 0; j < ap_pro[i]; j++) {
					m_xprojection.SetPixel(j, i, RGB(255, 255, 255));
				}
			}
		}
		else {
			for (int i = 0; i < m_img_width; i++) {
				for (int j = 0; j < ap_pro[i]; j++) {
					m_yprojection.SetPixel(i, j, RGB(255, 255, 255));
				}
			}
		}
	}
	else {
		CMFC_SDI_PREPROCESSView *pView = (CMFC_SDI_PREPROCESSView *)((CMainFrame *)(AfxGetApp()->m_pMainWnd))->GetActiveView();
		if (a_flag == 1) {
			for (int i = 0; i < pView->m_select_height_rate; i++) {
				for (int j = 0; j < ap_pro[i]; j++) {
					m_xprojection.SetPixel(j, i, RGB(255, 255, 255));
				}
			}
		}
		else {
			for (int i = 0; i < pView->m_select_width_rate; i++) {
				for (int j = 0; j < ap_pro[i]; j++) {
					m_yprojection.SetPixel(i, j, RGB(255, 255, 255));
				}
			}
		}
	}
}
void CMFC_SDI_PREPROCESSDoc::CFileInit(unsigned int a_filterindex) {
	CFile fp;

	fp.Open(m_filepath, CFile::modeRead | CFile::typeBinary);
	m_fileindex = a_filterindex;
	if (a_filterindex == 1) {
		fp.Seek(2, CFile::current);
		fp.Read(&m_size, 4);		//	File Size

		fp.Seek(4, CFile::current);
		fp.Read(&m_data_offset, 4);	//	File data offset

		fp.Seek(4, CFile::current);
		fp.Read(&m_img_width, 4);	//	File width
		fp.Read(&m_img_height, 4);	//	File height
		fp.Seek(2, CFile::current);
		fp.Read(&m_img_bit, 1);
		// (전체 크기 - (이미지너비 * 이미지 높이 * 3(RGB) + 54(이미지헤더크기)) / 이미지높이
		if (m_img_bit == 24)
			m_widthstep = (m_size - (m_img_width * m_img_height * 3 + 54)) / m_img_height;
		else
			m_widthstep = 0;
		fp.Seek(m_data_offset, CFile::begin);
		m_red = new unsigned char *[m_img_height];
		m_green = new unsigned char *[m_img_height];
		m_blue = new unsigned char *[m_img_height];
		m_gray = new unsigned char *[m_img_height];
		m_binary = new unsigned char *[m_img_height];
		m_sobel = new unsigned char *[m_img_height];
		m_gaussian = new unsigned char *[m_img_height];
		m_equal = new unsigned char *[m_img_height];
		m_stretch = new unsigned char *[m_img_height];
		m_xpro = new unsigned int[m_img_width];
		m_ypro = new unsigned int[m_img_height];
		m_LVQ_red = new unsigned char *[m_img_height];
		m_LVQ_green = new unsigned char *[m_img_height];
		m_LVQ_blue = new unsigned char *[m_img_height];
		for (int i = 0; i < m_img_height; i++) {
			m_red[i] = new unsigned char[m_img_width];
			m_green[i] = new unsigned char[m_img_width];
			m_blue[i] = new unsigned char[m_img_width];
			m_gray[i] = new unsigned char[m_img_width];
			m_binary[i] = new unsigned char[m_img_width];
			m_sobel[i] = new unsigned char[m_img_height];
			m_gaussian[i] = new unsigned char[m_img_height];
			m_equal[i] = new unsigned char[m_img_height];
			m_stretch[i] = new unsigned char[m_img_height];
			m_LVQ_red[i] = new unsigned char[m_img_width];
			m_LVQ_green[i] = new unsigned char[m_img_width];
			m_LVQ_blue[i] = new unsigned char[m_img_width];
		}

		for (int i = m_img_height - 1; i >= 0; i--) {
			for (int j = 0; j < m_img_width; j++) {
				fp.Read(&m_blue[i][j], 1);
				fp.Read(&m_green[i][j], 1);
				fp.Read(&m_red[i][j], 1);
				m_gray[i][j] = 255;
				m_binary[i][j] = 255;
			}
			if (m_widthstep)
				fp.Seek(m_widthstep, CFile::current);
		}
	}
	else if (a_filterindex == 2) {
		fp.Read(&m_img_width, 4);
		fp.Read(&m_img_height, 4);
		memset(m_his, 0, 256 * 4);
		m_widthstep = 0;
		m_org_image.Create(m_img_width, m_img_height, 24);
		m_change_image.Create(m_img_width, m_img_height, 24);
		int max = 0;
		m_red = new unsigned char *[m_img_height];
		m_green = new unsigned char *[m_img_height];
		m_blue = new unsigned char *[m_img_height];
		m_gray = new unsigned char *[m_img_height];
		m_binary = new unsigned char *[m_img_height];
		m_xpro = new unsigned int[m_img_height];
		m_ypro = new unsigned int[m_img_width];
		for (int i = 0; i < m_img_height; i++) {
			m_red[i] = new unsigned char[m_img_width];
			m_green[i] = new unsigned char[m_img_width];
			m_blue[i] = new unsigned char[m_img_width];
			m_gray[i] = new unsigned char[m_img_width];
			m_binary[i] = new unsigned char[m_img_width];
		}

		for (int i = 0; i < m_img_height; i++) {
			for (int j = 0; j < m_img_width; j++) {
				fp.Read(&m_gray[i][j], 1);
				m_his[m_gray[i][j]] += 1;
			}
		}
		m_max = m_img_height * m_img_width;
		m_histogram.Create(256, m_max + 1, m_org_image.GetBPP());
	}
	else if (a_filterindex == 3) {
		fp.Read(&m_img_width, 4);
		fp.Read(&m_img_height, 4);
		memset(m_his, 0, 256 * 4);
		m_widthstep = 0;
		m_org_image.Create(m_img_width, m_img_height, 24);
		m_change_image.Create(m_img_width, m_img_height, 24);
		int max = 0;
		m_red = new unsigned char *[m_img_height];
		m_green = new unsigned char *[m_img_height];
		m_blue = new unsigned char *[m_img_height];
		m_gray = new unsigned char *[m_img_height];
		m_binary = new unsigned char *[m_img_height];
		m_xpro = new unsigned int[m_img_height];
		m_ypro = new unsigned int[m_img_width];
		for (int i = 0; i < m_img_height; i++) {
			m_red[i] = new unsigned char[m_img_width];
			m_green[i] = new unsigned char[m_img_width];
			m_blue[i] = new unsigned char[m_img_width];
			m_gray[i] = new unsigned char[m_img_width];
			m_binary[i] = new unsigned char[m_img_width];
		}

		for (int i = 0; i < m_img_height; i++) {
			for (int j = 0; j < m_img_width; j++) {
				fp.Read(&m_gray[i][j], 1);
				fp.Seek(2, CFile::current);
				m_his[m_gray[i][j]] += 1;
			}
		}
		m_max = m_img_height * m_img_width;
		m_histogram.Create(256, m_max + 1, m_org_image.GetBPP());
	}
	fp.Close();

	UpdateAllViews(NULL);
}
void CMFC_SDI_PREPROCESSDoc::OnFileopen()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	TCHAR filter[] = _T("비트맵 파일(*.bmp)|*.bmp|raw 파일(*.raw)|*.raw|raw3 파일(*.raw3)|*.raw3|모든파일(*.*)|*.*");
	CFileDialog dlgFile(true, NULL, NULL, OFN_READONLY, filter);

	if (dlgFile.DoModal() == IDOK) {
		if (m_isfileopen) {
			m_isfileopen = false;
			m_org_image.Destroy();
			if (m_ischange) {
				m_ischange = false;
				m_change_image.Destroy();
				if (m_isgray)
					m_histogram.Destroy();
				if (m_isbinary) {
					m_xprojection.Destroy();
					m_yprojection.Destroy();
				}
				for (int i = 0; i < m_img_height; i++) {
					delete[] m_red[i];
					delete[] m_green[i];
					delete[] m_blue[i];
					delete[] m_binary[i];
					delete[] m_gray[i];
					delete[] m_LVQ_red[i];
					delete[] m_LVQ_green[i];
					delete[] m_LVQ_blue[i];
				}
				delete[] m_red;
				delete[] m_green;
				delete[] m_blue;
				delete[] m_gray;
				delete[] m_binary;
				delete[] m_xpro;
				delete[] m_ypro;
				delete[] m_LVQ_red;
				delete[] m_LVQ_green;
				delete[] m_LVQ_blue;
			}
		}

		m_isfileopen = true;
		m_isbinary = false;
		m_isgray = false;
		m_isEqual = false;
		m_isStret = false;
		m_isLVQ = false;
		m_isselect = false;
		m_filepath = dlgFile.GetPathName();
		CFileInit(dlgFile.m_ofn.nFilterIndex);

		if (dlgFile.m_ofn.nFilterIndex == 1) {
			m_org_image.Load(m_filepath);
		}
		else if (dlgFile.m_ofn.nFilterIndex == 2) {
			for (int i = 0; i < m_img_height; i++)
				for (int j = 0; j < m_img_width; j++) {
					m_org_image.SetPixel(j, i, RGB(m_gray[i][j], m_gray[i][j], m_gray[i][j]));
				}
		}
		else if (dlgFile.m_ofn.nFilterIndex == 3) {

		}
	}
	UpdateAllViews(NULL);
}
void CMFC_SDI_PREPROCESSDoc::OnFilesave()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	TCHAR filter[] = _T("비트맵 파일(*.bmp)|*.bmp|raw 파일(*.raw)|*.raw|raw3 파일(*.raw3)|*.raw3|모든파일(*.*)|*.*");
	CFileDialog dlgFile(false, NULL, NULL, OFN_HIDEREADONLY, filter);
	char *pstr;

	if (dlgFile.DoModal() == IDOK) {
		CFile fp;
		if (dlgFile.m_ofn.nFilterIndex == 1) {					//	bmp
			m_filepath = dlgFile.GetPathName();
			m_filepath += L".bmp";
			m_change_image.Save(m_filepath);
		}
		else if (dlgFile.m_ofn.nFilterIndex == 2) {				//	raw
			m_filepath = dlgFile.GetPathName();
			m_filepath += L".raw";
			fp.Open(m_filepath, CFile::modeCreate | CFile::modeWrite);
			fp.Write(&m_img_width, 4);
			fp.Write(&m_img_height, 4);
			for (int i = 0; i < m_img_height; i++) {
				for (int j = 0; j < m_img_width; j++) {
					fp.Write(&m_gray[i][j], 1);
				}
			}
			fp.Close();
		}
		else if (dlgFile.m_ofn.nFilterIndex == 3) {				//	raw3
			m_filepath = dlgFile.GetPathName();
			m_filepath += L".raw3";
			fp.Open(m_filepath, CFile::modeCreate | CFile::modeWrite);
			fp.Write(&m_img_width, 4);
			fp.Write(&m_img_height, 4);
			for (int i = 0; i < m_img_height; i++) {
				for (int j = 0; j < m_img_width; j++) {
					fp.Write(&m_gray[i][j], 1);
					fp.Write(&m_gray[i][j], 1);
					fp.Write(&m_gray[i][j], 1);
				}
			}
			fp.Close();
		}
	}
}
void CMFC_SDI_PREPROCESSDoc::OnGray()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	if (m_isfileopen) {
		if (!m_isselect) {
			m_ischange = true;
			DWORD adwBitmasks[3] = { 0x000000FF, 0x000000FF, 0x000000FF };
			int max = 0;
			if (!m_isgray)
				m_change_image.Create(m_img_width, m_img_height, m_org_image.GetBPP());
			else {
				for (int i = 0; i < m_img_height; i++) {
					for (int j = 0; j < m_img_width; j++) {
						m_change_image.SetPixel(j, i, RGB(m_gray[i][j], m_gray[i][j], m_gray[i][j]));
					}
				}
				UpdateAllViews(NULL);
				return;
			}
			m_isgray = true;
			/*m_change_image.CreateEx(m_img_width, m_img_height, m_org_image.GetBPP(), BI_BITFIELDS, adwBitmasks, 0);*/
			if (m_fileindex == 1) {
				memset(m_his, 0, 256 * 4);
				for (int i = 0; i < m_img_height; i++) {
					for (int j = 0; j < m_img_width; j++) {
						m_gray[i][j] = (m_red[i][j] * 0.2126 + m_green[i][j] * 0.7152 + m_blue[i][j] * 0.0722);
						/*(m_red[i][j] + m_green[i][j] + m_blue[i][j]) / 3;*/
						m_change_image.SetPixel(j, i, RGB(m_gray[i][j], m_gray[i][j], m_gray[i][j]));
						m_his[m_gray[i][j]]++;
					}
				}
				for (int i = 0; i < 256; i++) {
					m_his[i] = 10000 * m_his[i] / (m_img_height * m_img_width);
				}
				max = m_his[0];
				for (int i = 1; i < 256; i++) {
					if (m_his[i] > max)
						max = m_his[i];
				}
				m_histogram.Create(256, max, m_org_image.GetBPP());
			}
			else if (m_fileindex == 2) {
				for (int i = m_img_height - 1; i >= 0; i--) {
					for (int j = 0; j < m_img_width; j++) {
						m_change_image.SetPixel(j, i, RGB(m_gray[i][j], m_gray[i][j], m_gray[i][j]));
					}
				}
			}
			for (int i = 0; i < 256; i++) {
				for (int j = 0; j < max - m_his[i]; j++) {
					m_histogram.SetPixel(i, j, RGB(255, 255, 255));
					/*m_histogram.SetPixel(i, max - 1 - j, RGB(255, 255, 255));*/
				}
			}

			UpdateAllViews(NULL);
		}
		else {
			m_ischange = true;
			CMFC_SDI_PREPROCESSView *pView = (CMFC_SDI_PREPROCESSView *)((CMainFrame *)(AfxGetApp()->m_pMainWnd))->GetActiveView();

			DWORD adwBitmasks[3] = { 0x000000FF, 0x000000FF, 0x000000FF };
			int max = 0;
			if (!m_isgray)
				m_change_image.Create(pView->m_select_width_rate, pView->m_select_height_rate, m_org_image.GetBPP());
			else {
				for (int i = pView->m_y; i < pView->m_select_height_rate + pView->m_y; i++) {
					for (int j = pView->m_x; j < pView->m_select_width_rate + pView->m_x; j++) {
						m_change_image.SetPixel(j - pView->m_x, i - pView->m_y, RGB(m_gray[i][j], m_gray[i][j], m_gray[i][j]));
					}
				}
				UpdateAllViews(NULL);
				return;
			}
			m_isgray = true;
			/*m_change_image.CreateEx(m_img_width, m_img_height, m_org_image.GetBPP(), BI_BITFIELDS, adwBitmasks, 0);*/
			if (m_fileindex == 1) {
				memset(m_his, 0, 256 * 4);
				for (int i = pView->m_y; i < pView->m_select_height_rate + pView->m_y; i++) {
					for (int j = pView->m_x; j < pView->m_select_width_rate + pView->m_x; j++) {
						m_gray[i][j] = (m_red[i][j] * 0.2126 + m_green[i][j] * 0.7152 + m_blue[i][j] * 0.0722);
						/*(m_red[i][j] + m_green[i][j] + m_blue[i][j]) / 3;*/
						m_change_image.SetPixel(j - pView->m_x, i - pView->m_y, RGB(m_gray[i][j], m_gray[i][j], m_gray[i][j]));
						m_his[m_gray[i][j]]++;
					}
				}
				for (int i = 0; i < 256; i++) {
					m_his[i] = 10000 * m_his[i] / (pView->m_select_height_rate * pView->m_select_width_rate);
				}
				max = m_his[0];
				for (int i = 1; i < 256; i++) {
					if (m_his[i] > max)
						max = m_his[i];
				}
				m_histogram.Create(256, max, m_org_image.GetBPP());
			}
			else if (m_fileindex == 2) {
				for (int i = m_img_height - 1; i >= 0; i--) {
					for (int j = 0; j < m_img_width; j++) {
						m_change_image.SetPixel(j, i, RGB(m_gray[i][j], m_gray[i][j], m_gray[i][j]));
					}
				}
			}
			for (int i = 0; i < 256; i++) {
				for (int j = 0; j < max - m_his[i]; j++) {
					m_histogram.SetPixel(i, j, RGB(255, 255, 255));
					/*m_histogram.SetPixel(i, max - 1 - j, RGB(255, 255, 255));*/
				}
			}

			UpdateAllViews(NULL);
		}
	}
}
void CMFC_SDI_PREPROCESSDoc::OnBinary()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	if (m_isfileopen) {
		if (!m_isselect) {
			m_ischange = true;
			memset(m_xpro, 0, m_img_height * 4);
			memset(m_ypro, 0, m_img_width * 4);
			m_xprojection.Destroy();
			m_yprojection.Destroy();
			if (!m_isgray) {
				OnGray();
				m_isgray = true;
			}
			if (!m_isbinary) {
				GetThresHold();
				m_isbinary = true;
			}
			for (int i = 0; i < m_img_height; i++) {
				for (int j = 0; j < m_img_width; j++) {
					if (m_gray[i][j] > m_threshold) {
						m_binary[i][j] = 255;
						m_xpro[i]++;
						m_ypro[j]++;
					}
					else {
						m_binary[i][j] = 0;
					}
					m_change_image.SetPixel(j, i, RGB(m_binary[i][j], m_binary[i][j], m_binary[i][j]));
				}
			}
			m_xprojection.Create(m_img_width, m_img_height, m_org_image.GetBPP());
			m_yprojection.Create(m_img_width, m_img_height, m_org_image.GetBPP());
			LetProjection(m_xpro, 1);
			LetProjection(m_ypro, 2);

			UpdateAllViews(NULL);
		}
		else {
			int max, min;
			bool check = true;
			max = m_dlgthreshold.m_hslider_val_max;
			min = m_dlgthreshold.m_hslider_val_min;

			if (max < min) {
				check = false;
			}
			m_ischange = true;
			CMFC_SDI_PREPROCESSView *pView = (CMFC_SDI_PREPROCESSView *)((CMainFrame *)(AfxGetApp()->m_pMainWnd))->GetActiveView();
			memset(m_xpro, 0, pView->m_select_height_rate * 4);
			memset(m_ypro, 0, pView->m_select_width_rate * 4);
			m_xprojection.Destroy();
			m_yprojection.Destroy();
			if (!m_isgray) {
				OnGray();
				m_isgray = true;
			}
			if (!m_isbinary) {
				OnThresholdTwo();
				return;
			}
			if (check) {
				for (int i = pView->m_y; i < pView->m_select_height_rate + pView->m_y; i++) {
					for (int j = pView->m_x; j < pView->m_select_width_rate + pView->m_x; j++) {
						if (m_gray[i][j] > min && m_gray[i][j] < max) {
							m_binary[i][j] = 255;
							m_xpro[i - pView->m_y]++;
							m_ypro[j - pView->m_x]++;
						}
						else {
							m_binary[i][j] = 0;
						}
						m_change_image.SetPixel(j - pView->m_x, i - pView->m_y, RGB(m_binary[i][j], m_binary[i][j], m_binary[i][j]));
					}
				}
			}
			else {
				for (int i = pView->m_y; i < pView->m_select_height_rate + pView->m_y; i++) {
					for (int j = pView->m_x; j < pView->m_select_width_rate + pView->m_x; j++) {
						if (m_gray[i][j] > max && m_gray[i][j] < min) {
							m_binary[i][j] = 0;
						}
						else {
							m_binary[i][j] = 255;
							m_xpro[i - pView->m_y]++;
							m_ypro[j - pView->m_x]++;
						}
						m_change_image.SetPixel(j - pView->m_x, i - pView->m_y, RGB(m_binary[i][j], m_binary[i][j], m_binary[i][j]));
					}
				}
			}
			m_xprojection.Create(pView->m_select_width_rate, pView->m_select_height_rate, m_org_image.GetBPP());
			m_yprojection.Create(pView->m_select_width_rate, pView->m_select_height_rate, m_org_image.GetBPP());
			LetProjection(m_xpro, 1);
			LetProjection(m_ypro, 2);

			UpdateAllViews(NULL);
		}
	}
}
void CMFC_SDI_PREPROCESSDoc::OnThreshold()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	m_dlg.DoModal();
	m_threshold = m_dlg.m_hslider_val;
	OnBinary();
}
void CMFC_SDI_PREPROCESSDoc::OnSobel()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	int xmask[3][3] = { {-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1} };
	int ymask[3][3] = { {1, 2, 1}, {0, 0, 0}, {-1, -2, -1} };
	int xsum;
	int ysum;

	if (m_isfileopen) {
		m_ischange = true;
		if (!m_isgray) {
			OnGray();
			m_isgray = true;
		}
		if (!m_isbinary) {
			GetThresHold();
		}
		for (int i = 0; i < m_img_height - 2; i++) {
			for (int j = 0; j < m_img_width - 2; j++) {
				xsum = 0;
				ysum = 0;
				for (int x = 0; x < 3; x++) {
					for (int y = 0; y < 3; y++) {
						xsum += xmask[x][y] * m_gray[i + x][j + y];
						ysum += ymask[x][y] * m_gray[i + x][j + y];
					}
				}
				xsum = abs(xsum);
				ysum = abs(ysum);
				if (xsum + ysum > m_threshold) {
					m_sobel[i][j] = 255;
				}
				else
					m_sobel[i][j] = 0;
				m_change_image.SetPixel(j, i, RGB(m_sobel[i][j], m_sobel[i][j], m_sobel[i][j]));
			}
		}
		UpdateAllViews(NULL);
	}
}
void CMFC_SDI_PREPROCESSDoc::OnGaussian()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	int mask[3][3] = { { 1, 2, 1 },{ 2, 4, 2 },{ 1, 2, 1 } };
	int sum;

	if (m_isfileopen) {
		m_ischange = true;
		if (!m_isgray) {
			OnGray();
			m_isgray = true;
		}
		for (int i = 0; i < m_img_height - 2; i++) {
			for (int j = 0; j < m_img_width - 2; j++) {
				sum = 0;
				for (int x = 0; x < 3; x++) {
					for (int y = 0; y < 3; y++) {
						sum += mask[x][y] * m_gray[i + x][j + y];
					}
				}
				sum = sum / 16;	// mask 크기
				m_gaussian[i][j] = sum;

				m_change_image.SetPixel(j, i, RGB(m_gaussian[i][j], m_gaussian[i][j], m_gaussian[i][j]));
			}
		}
		UpdateAllViews(NULL);
	}
}
void CMFC_SDI_PREPROCESSDoc::OnEqualization()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	unsigned int *sum_his = new unsigned int[256];
	int sum = 0;
	int all_pixels, max;
	int temp;

	if (m_isfileopen) {
		m_ischange = true;
		m_isEqual = true;
		if (!m_isgray) {
			OnGray();
			m_isgray = true;
		}
		for (int i = 0; i < 256; i++) {
			sum += m_his[i];
			m_his[i] = 0;
			sum_his[i] = sum;
		}
		all_pixels = sum_his[255];
		for (int i = 0; i < m_img_height; i++) {
			for (int j = 0; j < m_img_width; j++) {
				temp = (int)(sum_his[m_gray[i][j]] * 255 / all_pixels);
				m_change_image.SetPixel(j, i, RGB(temp, temp, temp));
				m_his[temp]++;
			}
		}
		for (int i = 0; i < 256; i++) {
			m_his[i] = 10000 * m_his[i] / (m_img_height * m_img_width);
		}
		max = m_his[0];
		for (int i = 1; i < 256; i++) {
			if (m_his[i] > max)
				max = m_his[i];
		}for (int i = 0; i < 256; i++) {
			for (int j = 0; j < max - m_his[i]; j++) {
				m_histogram.SetPixel(i, j, RGB(255, 255, 255));
			}
		}

		delete[] sum_his;
		UpdateAllViews(NULL);
	}
}
void CMFC_SDI_PREPROCESSDoc::OnStretching()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	if (m_isfileopen) {
		m_ischange = true;
		m_isStret = true;
		if (!m_isgray) {
			OnGray();
			m_isgray = true;
		}
		int left, right;
		int sum = 0;
		int temp;
		int max, min;

		for (int i = 1; i < 255; i++) {
			if (m_his[i] > 0) {
				min = i;
				break;
			}
		}
		for (int i = 254; i >= 0; i--) {
			if (m_his[i] > 0) {
				max = i;
				break;
			}
		}
		memset(m_his, 0, 256 * 4);
		if ((max - min) == 0)
			min = min - 1;
		for (int i = 0; i < m_img_height; i++) {
			for (int j = 0; j < m_img_width; j++) {
				temp = (int)((m_gray[i][j] - min) * 255 / (max - min));
				m_change_image.SetPixel(j, i, RGB(temp, temp, temp));
				m_his[temp]++;
			}
		}
		for (int i = 0; i < 256; i++) {
			m_his[i] = 10000 * m_his[i] / (m_img_height * m_img_width);
		}
		max = m_his[0];
		for (int i = 1; i < 256; i++) {
			if (m_his[i] > max)
				max = m_his[i];
		}for (int i = 0; i < 256; i++) {
			for (int j = 0; j < max - m_his[i]; j++) {
				m_histogram.SetPixel(i, j, RGB(255, 255, 255));
			}
		}
		UpdateAllViews(NULL);
	}
}
void CMFC_SDI_PREPROCESSDoc::OnLvq()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.

	float learning_rate = 0.01;		// 학습율
	int cycle_count = 0;			// 학습 횟수
	int sum = INT_MAX;				// 학습을 종료시키기 위한 하나의 flag
	int temp_sum = 0;				// sum 값 임시 저장
	int temp;						// 최단 거리
	int x = 0;							// 최단 거리일 때의 index 값
	int min;
	int r, g, b;

	/*for (int i = 0; i < m_img_height; i++) {
		delete[] m_LVQ_red[i];
		delete[] m_LVQ_green[i];
		delete[] m_LVQ_blue[i];
	}
	delete[] m_LVQ_red;
	delete[] m_LVQ_green;
	delete[] m_LVQ_blue;*/

	if (m_isfileopen) {
		m_ischange = true;
		if (!m_isLVQ) {
			m_isLVQ = true;
			m_change_image.Create(m_img_width, m_img_height, m_org_image.GetBPP());
		}

		m_dlgLVQ.DoModal();
		m_referencevector = _ttoi(m_dlgLVQ.m_edit_val);

		float **cluster;

		cluster = new float*[3];
		for (int i = 0; i < m_referencevector; i++) {
			*(cluster + i) = new float[3];
			memset(*(cluster + i), 0, sizeof(float) * 3);
		}

		srand(time(NULL));
		for (int i = 0; i < m_referencevector; i++) {
			for (int j = 0; j < 3; j++) {
				cluster[i][j] = (int)(rand() % 256);
			}
		}


		// 학습 횟수는 최대 8회이며
		// 학습이 계속 되어도 sum 의 값에 변화가 없을 경우 학습을 종료한다.
		while (cycle_count < 8 && sum != temp_sum) {
			cycle_count++;

			temp_sum = sum;
			sum = 0;

			for (int i = 0; i < m_img_height; i++) {
				for (int j = 0; j < m_img_width; j++) {
					min = INT_MAX;
					for (int k = 0; k < m_referencevector; k++) {
						// 군집과 rgb 값을 뺀 값을 전부 더해 그 값이 가장 작을 때 최단 거리이다
						temp = abs((float)m_red[i][j] - cluster[k][0]) +
							abs((float)m_green[i][j] - cluster[k][1]) +
							abs((float)m_blue[i][j] - cluster[k][2]);
						if (min > temp) {
							min = temp;
							x = k;
						}
					}
					r = (int)abs((float)m_red[i][j] - cluster[x][0]);
					g = (int)abs((float)m_green[i][j] - cluster[x][1]);
					b = (int)abs((float)m_blue[i][j] - cluster[x][2]);

					cluster[x][0] += learning_rate * ((float)m_red[i][j] - cluster[x][0]);
					cluster[x][1] += learning_rate * ((float)m_green[i][j] - cluster[x][1]);
					cluster[x][2] += learning_rate * ((float)m_blue[i][j] - cluster[x][2]);

					sum += r + g + b;
				}
			}
		}
		for (int i = 0; i < m_img_height; i++) {
			for (int j = 0; j < m_img_width; j++) {
				min = INT_MAX;
				for (int k = 0; k < m_referencevector; k++) {
					// 군집과 rgb 값을 뺀 값을 전부 더해 그 값이 가장 작을 때 최단 거리이다
					temp = abs((float)m_red[i][j] - cluster[k][0]) +
						abs((float)m_green[i][j] - cluster[k][1]) +
						abs((float)m_blue[i][j] - cluster[k][2]);
					if (min > temp) {
						min = temp;
						x = k;
					}
				}
				m_change_image.SetPixel(j, i, RGB((BYTE)cluster[x][0], (BYTE)cluster[x][1], (BYTE)cluster[x][2]));
				m_LVQ_red[i][j] = (BYTE)cluster[x][0];
				m_LVQ_green[i][j] = (BYTE)cluster[x][1];
				m_LVQ_blue[i][j] = (BYTE)cluster[x][2];
			}
		}
	}
	UpdateAllViews(NULL);
}
void CMFC_SDI_PREPROCESSDoc::OnLabeling()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	if (m_isfileopen) {
		m_ischange = true;
		m_islabeling = true;

		ToBinary();
		ToLabeling();
	}
}
void CMFC_SDI_PREPROCESSDoc::ToBinary() {


	for (int i = 0; i < m_img_height; i++) {
		for (int j = 0; j < m_img_width; j++) {
			if (m_LVQ_red[i][j] == GetRValue(m_rgb) &&
				m_LVQ_green[i][j] == GetGValue(m_rgb) &&
				m_LVQ_blue[i][j] == GetBValue(m_rgb)) {
				m_binary[i][j] = 255;
			}
			else {
				m_binary[i][j] = 0;
			}
		}
	}
}
void CMFC_SDI_PREPROCESSDoc::ToLabeling() {

	int **map, eql_table[100000][2] = { {0,}, };
	int label = 0;
	int max, min;

	map = new int *[m_img_height];
	for (int i = 0; i < m_img_height; i++) {
		*(map + i) = new int[m_img_width];
		memset(*(map + i), 0, sizeof(int) * m_img_width);
	}

	for (int i = 0; i < m_img_height; i++) {
		for (int j = 0; j < m_img_width; j++) {
			if (m_binary[i][j] != 0) {
				// 새로운 레이블
				if (i == 0 && j == 0) {
					label++;
					map[i][j] = label;
					eql_table[label][0] = label;
					eql_table[label][1] = label;
				}
				// 첫번째 행에 있고 왼쪽 레이블이 없을 때
				else if (i == 0 && map[i][j - 1] == 0) {
					label++;
					map[i][j] = label;
					eql_table[label][0] = label;
					eql_table[label][1] = label;
				}
				// 첫번쨰 행에 있고 왼쪽 레이블이 존재할 때
				else if (i == 0 && map[i][j - 1] != 0) {
					map[i][j] = map[i][j - 1];
				}
				// 첫번째 열에 있고 위쪽 레이블이 없을 때
				else if (j == 0 && map[i - 1][j] == 0) {
					label++;
					map[i][j] = label;
					eql_table[label][0] = label;
					eql_table[label][1] = label;
				}
				// 첫번잰 열에 있고 위쪽 레이블이 존재할 때
				else if (j == 0 && map[i - 1][j] != 0) {
					map[i][j] = map[i - 1][j];
				}
				else {
					// 두 이웃한 픽셀 모두 레이블이 존재하고 두 레이블이 같을 때
					if (map[i - 1][j] != 0 && map[i][j - 1] != 0) {
						if (map[i - 1][j] == map[i][j - 1]) {
							map[i][j] = map[i - 1][j];
						}
						// 두 이웃한 픽셀 모두 레이블이 존재하고 두 레이블이 다를 때
						else {
							max = (map[i][j - 1] > map[i - 1][j]) ? map[i][j - 1] : map[i - 1][j];
							min = (map[i][j - 1] > map[i - 1][j]) ? map[i - 1][j] : map[i][j - 1];

							map[i][j] = min;
							eql_table[max][1] = min;
						}
					}
					// 왼쪽 혹은 위쪽 즉, 두 이웃한 픽셀중 한군데만 레이블이 있을 때
					else if (map[i][j - 1] != 0 && map[i - 1][j] == 0) {	 // 왼쪽
						map[i][j] = map[i][j - 1];
					}
					else if (map[i][j - 1] == 0 && map[i - 1][j] != 0) {	 // 위쪽
						map[i][j] = map[i - 1][j];
					}
					// 새로운 레이블일 때
					else {
						label++;
						map[i][j] = label;
						eql_table[label][0] = label;
						eql_table[label][1] = label;
					}
				}
			}
		}
	}


	int temp;
	for (int i = 1; i <= label; i++) {
		temp = i;
		while (temp != eql_table[temp][1]) {
			temp = eql_table[temp][1];
		}
		eql_table[i][1] = eql_table[temp][1];
	}

	for (int i = 0; i < m_img_height; i++) {
		for (int j = 0; j < m_img_width; j++) {
			if (map[i][j] != 0) {
				m_change_image.SetPixel(j, i, RGB(255, 255, 0));
			}
		}
	}

	for (int i = 0; i < m_img_height; i++) {
		delete[] map[i];
	}
	delete[] map;

	UpdateAllViews(NULL);
}
void CMFC_SDI_PREPROCESSDoc::OnThresholdTwo()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	m_dlgthreshold.DoModal();

	bool check = true;
	int max, min;
	max = m_dlgthreshold.m_hslider_val_max;
	min = m_dlgthreshold.m_hslider_val_min;

	if (max < min) {
		check = false;
	}
	if (m_isfileopen) {
		if (!m_isselect) {
			m_ischange = true;
			memset(m_xpro, 0, m_img_height * 4);
			memset(m_ypro, 0, m_img_width * 4);
			m_xprojection.Destroy();
			m_yprojection.Destroy();
			if (!m_isgray) {
				OnGray();
				m_isgray = true;
			}
			m_isbinary = true;

			if (check) {
				for (int i = 0; i < m_img_height; i++) {
					for (int j = 0; j < m_img_width; j++) {
						if (m_gray[i][j] > min && m_gray[i][j] < max) {
							m_binary[i][j] = 255;
							m_xpro[i]++;
							m_ypro[j]++;
						}
						/*else if (m_gray[i][j] < max) {
							m_binary[i][j] = 255;
							m_xpro[i]++;
							m_ypro[j]++;
						}*/
						else {
							m_binary[i][j] = 0;
						}
						m_change_image.SetPixel(j, i, RGB(m_binary[i][j], m_binary[i][j], m_binary[i][j]));
					}
				}
			}
			else {
				for (int i = 0; i < m_img_height; i++) {
					for (int j = 0; j < m_img_width; j++) {
						if (m_gray[i][j] > max && m_gray[i][j] < min) {
							m_binary[i][j] = 0;
						}
						/*else if (m_gray[i][j] < max) {
						m_binary[i][j] = 255;
						m_xpro[i]++;
						m_ypro[j]++;
						}*/
						else {
							m_binary[i][j] = 255;
							m_xpro[i]++;
							m_ypro[j]++;
						}
						m_change_image.SetPixel(j, i, RGB(m_binary[i][j], m_binary[i][j], m_binary[i][j]));
					}
				}
			}
			m_xprojection.Create(m_img_width, m_img_height, m_org_image.GetBPP());
			m_yprojection.Create(m_img_width, m_img_height, m_org_image.GetBPP());
			LetProjection(m_xpro, 1);
			LetProjection(m_ypro, 2);

			UpdateAllViews(NULL);
		}
		else {
			m_ischange = true;
			CMFC_SDI_PREPROCESSView *pView = (CMFC_SDI_PREPROCESSView *)((CMainFrame *)(AfxGetApp()->m_pMainWnd))->GetActiveView();

			memset(m_xpro, 0, pView->m_select_height_rate * 4);
			memset(m_ypro, 0, pView->m_select_width_rate * 4);
			m_xprojection.Destroy();
			m_yprojection.Destroy();
			if (!m_isgray) {
				OnGray();
				m_isgray = true;
			}
			m_isbinary = true;

			if (check) {
				for (int i = pView->m_y; i < pView->m_select_height_rate + pView->m_y; i++) {
					for (int j = pView->m_x; j < pView->m_select_width_rate + pView->m_x; j++) {
						if (m_gray[i][j] > min && m_gray[i][j] < max) {
							m_binary[i][j] = 255;
							m_xpro[i - pView->m_y]++;
							m_ypro[j - pView->m_x]++;
						}
						/*else if (m_gray[i][j] < max) {
						m_binary[i][j] = 255;
						m_xpro[i]++;
						m_ypro[j]++;
						}*/
						else {
							m_binary[i][j] = 0;
						}
						m_change_image.SetPixel(j - pView->m_x, i - pView->m_y, RGB(m_binary[i][j], m_binary[i][j], m_binary[i][j]));
					}
				}
			}
			else {
				for (int i = pView->m_y; i < pView->m_select_height_rate + pView->m_y; i++) {
					for (int j = pView->m_x; j < pView->m_select_width_rate + pView->m_y; j++) {
						if (m_gray[i][j] > max && m_gray[i][j] < min) {
							m_binary[i][j] = 0;
						}
						/*else if (m_gray[i][j] < max) {
						m_binary[i][j] = 255;
						m_xpro[i]++;
						m_ypro[j]++;
						}*/
						else {
							m_binary[i][j] = 255;
							m_xpro[i - pView->m_y]++;
							m_ypro[j - pView->m_x]++;
						}
						m_change_image.SetPixel(j - pView->m_x, i - pView->m_y, RGB(m_binary[i][j], m_binary[i][j], m_binary[i][j]));
					}
				}
			}
			m_xprojection.Create(pView->m_select_width_rate, pView->m_select_height_rate, m_org_image.GetBPP());
			m_yprojection.Create(pView->m_select_width_rate, pView->m_select_height_rate, m_org_image.GetBPP());
			LetProjection(m_xpro, 1);
			LetProjection(m_ypro, 2);

			UpdateAllViews(NULL);
		}
	}
}
void CMFC_SDI_PREPROCESSDoc::OnSelectArea()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.

	m_isselect = true;
}


void CMFC_SDI_PREPROCESSDoc::OnGraySave()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.

	FILE *fp;
	fopen_s(&fp, "442_gray_1.txt", "w");
	CMFC_SDI_PREPROCESSView *pView = (CMFC_SDI_PREPROCESSView *)((CMainFrame *)(AfxGetApp()->m_pMainWnd))->GetActiveView();

	if (m_isselect) {
		fprintf(fp, "%d", pView->m_x);
		fprintf(fp, "\t");
		fprintf(fp, "%d", pView->m_y);
		fprintf(fp, "\t");
		fprintf(fp, "%d", m_img_height);
		fprintf(fp, "\t");
		fprintf(fp, "%d", m_img_width);
		fprintf(fp, "\t");
		fprintf(fp, "%d", pView->m_select_height_rate);
		fprintf(fp, "\t");
		fprintf(fp, "%d", pView->m_select_width_rate);
		fprintf(fp, "\n");
		for (int i = pView->m_y; i < pView->m_select_height_rate + pView->m_y; i++) {
			for (int j = pView->m_x; j < pView->m_select_width_rate + pView->m_x; j++) {
				fprintf(fp, "%3d", m_gray[i][j]);
				fprintf(fp, "\t");
			}
			fprintf(fp, "\n");
		}
	}
	else {
		fprintf(fp, "0\t0\t");
		fprintf(fp, "%d", m_img_height);
		fprintf(fp, "\t");
		fprintf(fp, "%d", m_img_width);
		fprintf(fp, "\t");
		fprintf(fp, "%d", m_img_height);
		fprintf(fp, "\t");
		fprintf(fp, "%d", m_img_width);
		fprintf(fp, "\n");
		for (int i = 0; i < m_img_height; i++) {
			for (int j = 0; j < m_img_width; j++) {
				fprintf(fp, "%3d", m_gray[i][j]);
				fprintf(fp, "\t");
			}
			fprintf(fp, "\n");
		}
	}
	fclose(fp);
}


void CMFC_SDI_PREPROCESSDoc::OnCenterPoint()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	FILE *fp;
	int *xPos, *yPos;
	int count;
	CMFC_SDI_PREPROCESSView *pView = (CMFC_SDI_PREPROCESSView *)((CMainFrame *)(AfxGetApp()->m_pMainWnd))->GetActiveView();
	/*fopen_s(&fp, "442.txt", "r");

	fgets(buf, 4, fp);

	coordinate = (unsigned int **)malloc(sizeof(int *) * (buf[0] - 48));
	for (int i = 0; i < buf[0] - 48; i++) {
		coordinate[i] = (unsigned int *)malloc(sizeof(int) * 7);

		str.Format(L"%d", (i + 1));

		m_dlglist.m_listinfo.InsertItem(i, str);
		fscanf_s(fp, "%d", &coordinate[i][0]);
		fscanf_s(fp, "%d", &coordinate[i][1]);
		temp.Format(L"%d", &coordinate[i][0]);
		temp = temp + L", ";
		temp.Format(L"%d", coordinate[i][1]);

		m_dlglist.m_listinfo.SetItem(i, 1, LVIF_TEXT, temp, 0, 0, 0, NULL);

		for (int j = coordinate[i][1] - 1; j <= coordinate[i][1] + 1; j++) {
			for (int k = coordinate[i][0] - 1; k <= coordinate[i][0] + 1; k++) {
				sum = sum + m_gray[j][k];
			}
		}
		avg = (float)sum / 9.0;
		coordinate[i][2] = avg;
	}*/
	fopen_s(&fp, "442.txt", "r");

	fscanf_s(fp, "%d\n", &count);

	xPos = new int[count];
	yPos = new int[count];

	for (int i = 0; i < count; i++)
		fscanf_s(fp, "%d\t%d\n", &xPos[i], &yPos[i]);

	if (m_isselect) {
		for (int i = 0; i < count; i++) {
			xPos[i] = xPos[i] - pView->m_x;
			yPos[i] = yPos[i] - pView->m_y;
			for (int y = 0; y < 5; y++) {
				for (int x = 0; x < 5; x++) {
					m_change_image.SetPixel(xPos[i] - 2 + x, yPos[i] - 2 + y, RGB(255, 0, 0));
				}
			}
		}
	}
	else {
		for (int i = 0; i < count; i++) {
			for (int y = 0; y < 5; y++) {
				for (int x = 0; x < 5; x++) {
					m_change_image.SetPixel(xPos[i] - 2 + x, yPos[i] - 2 + y, RGB(255, 0, 0));
				}
			}
		}
	}

	UpdateAllViews(NULL);

	m_dlglist.DoModal();
		
	UpdateAllViews(NULL);
}
