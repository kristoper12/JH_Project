// Dlg_List.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "MFC_SDI_PREPROCESS.h"
#include "Dlg_List.h"
#include "afxdialogex.h"
#include "MFC_SDI_PREPROCESSDoc.h"


// Dlg_List 대화 상자입니다.

IMPLEMENT_DYNAMIC(Dlg_List, CDialogEx)

Dlg_List::Dlg_List(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG4, pParent)
{
	/*UpdateData(TRUE);

	m_listinfo.SetExtendedStyle(LVS_EX_GRIDLINES);
	m_listinfo.InsertColumn(0, L"No.", LVCFMT_CENTER, 50);
	m_listinfo.InsertColumn(1, L"영역 중심 좌표", LVCFMT_CENTER, 100);
	m_listinfo.InsertColumn(2, L"평균", LVCFMT_CENTER, 90);
	m_listinfo.InsertColumn(3, L"표준 편차", LVCFMT_CENTER, 90);
	m_listinfo.InsertColumn(4, L"알파 * 표준 편차", LVCFMT_CENTER, 100);
	m_listinfo.InsertColumn(5, L"경계 좌표", LVCFMT_CENTER, 100);
	m_listinfo.InsertColumn(6, L"Old Gray 값", LVCFMT_CENTER, 100);
	m_listinfo.InsertColumn(7, L"New Gray 값", LVCFMT_CENTER, 100);*/
}

Dlg_List::~Dlg_List()
{
}

void Dlg_List::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST2, m_listinfo);
}


BEGIN_MESSAGE_MAP(Dlg_List, CDialogEx)
END_MESSAGE_MAP()


// Dlg_List 메시지 처리기입니다.


BOOL Dlg_List::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	m_listinfo.SetExtendedStyle(LVS_EX_GRIDLINES);
	m_listinfo.InsertColumn(0, L"No.", LVCFMT_CENTER, 50);
	m_listinfo.InsertColumn(1, L"영역 중심 좌표", LVCFMT_CENTER, 100);
	m_listinfo.InsertColumn(2, L"평균", LVCFMT_CENTER, 90);
	m_listinfo.InsertColumn(3, L"표준 편차", LVCFMT_CENTER, 90);
	m_listinfo.InsertColumn(4, L"알파 * 표준 편차", LVCFMT_CENTER, 100);
	m_listinfo.InsertColumn(5, L"경계 좌표", LVCFMT_CENTER, 100);
	m_listinfo.InsertColumn(6, L"Old Gray 값", LVCFMT_CENTER, 100);
	m_listinfo.InsertColumn(7, L"New Gray 값", LVCFMT_CENTER, 100);

	FILE *fp;
	FILE *fp_gray;
	char buf[5];
	CString str;
	CString temp;
	int sum = 0;
	float fsum = 0;
	float v;
	float o;
	int height, width;
	int org_height, org_width;
	char input1[100];
	char input2[1000];
	char *pch1;
	char *pch2;
	char *context;
	float avg;
	unsigned int **org_coordinate;
	unsigned int **coordinate;
	float **result;
	BYTE **gray;
	int x = 0, y = 0;
	int m_x, m_y;

	m_dlginsert.m_dlg = this;
	m_dlginsert.DoModal();

	fopen_s(&fp_gray, "442_gray_1.txt", "r");

	/*fgets(input1, 24, fp_gray);
	pch1 = strtok_s(input1, "\t", &context);
	m_x = atoi(pch1);
	pch1 = strtok_s(context, "\t", &context);
	m_y = atoi(pch1);
	pch1 = strtok_s(context, "\t", &context);
	org_height = atoi(pch1);
	pch1 = strtok_s(context, "\t", &context);
	org_width = atoi(pch1);
	pch1 = strtok_s(context, "\t", &context);
	height = atoi(pch1);
	pch1 = strtok_s(context, "\t", &context);
	width = atoi(pch1);
	pch1 = strtok_s(context, "\t", &context);*/
	fscanf_s(fp_gray, "%d\t%d\t%d\t%d\t%d\t%d\n", &m_x, &m_y, &org_height, &org_width, &height, &width);

	gray = new BYTE *[height];
	for (int i = 0; i < height; i++) {
		gray[i] = new BYTE[width];
	}

	for (y = 0; y < height; y++) {
		for (x = 0; x < width - 1; x++) {
			fscanf_s(fp_gray, "%d\t", &gray[y][x]);
			/*fgets(input2, width * 2, fp_gray);
			pch2 = strtok_s(input2, "\t", &context);
			while (pch2 != NULL){
				gray[i][x] = atoi(pch2);
				pch2 = strtok_s(context, "\t", &context);
				x++;
			}
			x = 0;
			if (feof(fp_gray))
				break;*/
		}
		fscanf_s(fp_gray, "%d\n", &gray[y][x]);
	}
	fclose(fp_gray);

	fopen_s(&fp, "442.txt", "r");
	fgets(buf, 4, fp);
	coordinate = (unsigned int **)malloc(sizeof(int *) * (buf[0] - 48));
	org_coordinate = (unsigned int **)malloc(sizeof(int *) * (buf[0] - 48));
	result = (float **)malloc(sizeof(float *) * (buf[0] - 48));
	int distinct = (m_Radius / 2);
	for (int i = 0; i < buf[0] - 48; i++) {
		coordinate[i] = (unsigned int *)malloc(sizeof(int) * 2);
		org_coordinate[i] = (unsigned int *)malloc(sizeof(int) * 2);
		result[i] = (float *)malloc(sizeof(float) * 3);

		str.Format(L"%d", (i + 1));

		m_listinfo.InsertItem(i, str);
		fscanf_s(fp, "%d", &org_coordinate[i][0]);
		fscanf_s(fp, "%d", &org_coordinate[i][1]);

		coordinate[i][0] = org_coordinate[i][0] - m_x;
		coordinate[i][1] = org_coordinate[i][1] - m_y;

		if ((height - org_height == 0) && (width - org_width == 0)) {
			temp.Format(L"%d, %d", org_coordinate[i][0], org_coordinate[i][1]);
		}
		else {
			temp.Format(L"%d, %d", coordinate[i][0], coordinate[i][1]);
		}

		m_listinfo.SetItem(i, 1, LVIF_TEXT, temp, 0, 0, 0, NULL);

		sum = 0;
		for (int j = coordinate[i][1] - distinct; j <= coordinate[i][1] + distinct; j++) {
			for (int k = coordinate[i][0] - distinct; k <= coordinate[i][0] + distinct; k++) {
				sum = sum + gray[j][k];
			}
		}
		avg = (float)sum / (float)(m_Radius * m_Radius);
		result[i][0] = avg;

		fsum = 0;
		for (int j = coordinate[i][1] - distinct; j <= coordinate[i][1] + distinct; j++) {
			for (int k = coordinate[i][0] - distinct; k <= coordinate[i][0] + distinct; k++) {
				fsum = fsum + pow(gray[j][k] - result[i][0], 2);
			}
		}
		v = fsum / (float)(m_Radius * m_Radius);
		o = sqrt(v);
		result[i][1] = o;
		result[i][2] = o * m_Alpha;

		temp.Format(L"%lf", result[i][0]);
		m_listinfo.SetItem(i, 2, LVIF_TEXT, temp, 0, 0, 0, NULL);
		temp.Format(L"%lf", result[i][1]);
		m_listinfo.SetItem(i, 3, LVIF_TEXT, temp, 0, 0, 0, NULL);
		temp.Format(L"%lf", result[i][2]);
		m_listinfo.SetItem(i, 4, LVIF_TEXT, temp, 0, 0, 0, NULL);
	}
	fclose(fp);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}
