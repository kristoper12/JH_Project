#include "Checked.h"
#include "File.h"
#include "resource.h"
#define MAX_COUNT 1000

LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam);
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,			//	WINAPI : ������ ���α׷��̶�� �ǹ�
	LPSTR lpszCmdLine, int nCmdShow)										//	hInstance : �ü���� Ŀ���� ���� ���α׷��� �ο��� ID
{																			//	szCmdLine : Ŀ��Ʈ���� �󿡼� ���α׷� ���� �� ���޵� ���ڿ�
	WNDCLASS WndClass;											 //	WndClass ��� ����ü ����									 
	WndClass.style = CS_HREDRAW | CS_VREDRAW;					 //	��½�Ÿ�� : ����/������ ��ȭ�� �ٽ� �׸�
	WndClass.lpfnWndProc = (WNDPROC)WndProc;					 //	���ν��� �Լ���
	WndClass.cbClsExtra = 0;									 //	O/S ��� ���� �޸� (Class)
	WndClass.cbWndExtra = 0;									 //	O/s ��� ���� �޸� (Window)
	WndClass.hInstance = hInstance;								 //	���� ���α׷� ID
	WndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);			 //	������ ����
	WndClass.hCursor = LoadCursor(NULL, IDC_ARROW);				 //	Ŀ�� ����
	WndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);//	����   
	WndClass.lpszMenuName = MAKEINTRESOURCE(IDR_MENU1);			 //	�޴� �̸�
	WndClass.lpszClassName = L"201431020_������";				 //	Ŭ���� �̸�
	RegisterClass(&WndClass);									 //	�ռ� ������ ������ Ŭ������ �ּ�
	HWND	hwnd;												 //	iCmdShow : �����찡 ȭ�鿡 ��µ� ����
	hwnd = CreateWindow(L"201431020_������",					 //	�����찡 �����Ǹ� �ڵ�(hwnd)�� ��ȯ
		L"201431020_������",									 //	������ Ŭ����, Ÿ��Ʋ �̸�
		WS_OVERLAPPEDWINDOW,									 //	������ ��Ÿ��
		CW_USEDEFAULT,											 //	������ ��ġ, x��ǥ
		CW_USEDEFAULT,											 //	������ ��ġ, y��ǥ
		CW_USEDEFAULT,											 //	������ ��   
		CW_USEDEFAULT,											 //	������ ����   
		// CW_USEDEFAULT
		NULL,													 //	�θ� ������ �ڵ�	 
		NULL,													 //	�޴� �ڵ�
		hInstance,    											 //	���� ���α׷� ID
		NULL     												 //	������ ������ ����
		);
	ShowWindow(hwnd, SW_SHOW);									 //	�������� ȭ�� ���
	UpdateWindow(hwnd);											 //	O/S �� WM_PAINT �޽��� ����
	MSG		msg;
	while (GetMessage(&msg, NULL, 0, 0))						 //	WinProc()���� PostQuitMessage() ȣ�� ������ ó��
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);									 //	WinMain -> WinProc  
	}
	return msg.wParam;
}

HDC hdc;
HDC hMemDC;
HANDLE hFile;
HBITMAP hBitmap, Old_hBitmap;
int g_is_clicked;
int penType = 0;
int penSize = 1;
int cnt = 0;
HBRUSH hBrush;
HBRUSH Old_hBrush;
HPEN hPen;
HPEN Old_hPen;
COLORREF pColor;
COLORREF bColor;
BOOL tBaseLine;
BOOL tFreeLine;
BOOL tDottedLine;
BOOL tCircle;
BOOL tTriangle;
BOOL tRectangle;
BOOL FileCheck;
RECT crt;
RECT r;
OPENFILENAME OFN;
TCHAR lpstrFile[100] = { NULL };
DWORD dwRead;
BITMAPFILEHEADER fh;
BITMAPINFOHEADER ih;
RGBQUAD rgb[256];
BYTE *pData;
DWORD dwDataSize;
DWORD dwPitch;
DWORD dwAddr;

LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	Checked KJH;
	File KJHfile;
	PAINTSTRUCT ps;
	static int xPos = 0, yPos = 0;
	static int Old_xPos = 0, Old_yPos = 0;

	switch (iMsg) {
	case WM_CREATE:
		hdc = GetDC(hwnd);
		tBaseLine = FALSE;
		tFreeLine = TRUE;
		GetClientRect(hwnd, &crt);
		hBitmap = CreateCompatibleBitmap(hdc, crt.right, crt.bottom);
		hMemDC = CreateCompatibleDC(hdc);
		Old_hBitmap = (HBITMAP)SelectObject(hMemDC, hBitmap);
		PatBlt(hMemDC, 0, 0, crt.right, crt.bottom, WHITENESS);
		break;
	case WM_PAINT:
		hdc = BeginPaint(hwnd, &ps);

		BitBlt(hdc, 0, 0, crt.right, crt.bottom, hMemDC, 0, 0, SRCCOPY);
		EndPaint(hwnd, &ps);
		break;
	case WM_LBUTTONDOWN:
		Old_xPos = LOWORD(lParam);
		Old_yPos = HIWORD(lParam);
		g_is_clicked = 1;
		xPos = Old_xPos;
		yPos = Old_yPos;
		break;
	case WM_LBUTTONUP:
		
		g_is_clicked = 0;
		hPen = CreatePen(penType, penSize, pColor);		// �� Ÿ��, ����, ����
		Old_hPen = (HPEN)SelectObject(hMemDC, hPen);
		hBrush = CreateSolidBrush(bColor);
		Old_hBrush = (HBRUSH)SelectObject(hMemDC, hBrush);
		SetROP2(hMemDC, R2_COPYPEN);
		if (pColor == 16777215)
			SetROP2(hMemDC, R2_MERGEPEN);
		SelectObject(hMemDC, hPen);
		SelectObject(hMemDC, hBrush);
		if (tBaseLine || tDottedLine){
			MoveToEx(hMemDC, Old_xPos, Old_yPos, NULL);
			LineTo(hMemDC, xPos, yPos);
			xPos = LOWORD(lParam);
			yPos = HIWORD(lParam);
			MoveToEx(hMemDC, Old_xPos, Old_yPos, NULL);
			LineTo(hMemDC, xPos, yPos);

		}
		else if (tFreeLine){
			SetROP2(hMemDC, R2_COPYPEN);
			MoveToEx(hMemDC, Old_xPos, Old_yPos, NULL);
			LineTo(hMemDC, xPos, yPos);
			Old_xPos = xPos;
			Old_yPos = yPos;
			xPos = LOWORD(lParam);
			yPos = HIWORD(lParam);
		}
		else if (tCircle){
			Ellipse(hMemDC, Old_xPos, Old_yPos, xPos, yPos);
			xPos = LOWORD(lParam);
			yPos = HIWORD(lParam);
			Ellipse(hMemDC, Old_xPos, Old_yPos, xPos, yPos);
		}
		else if (tTriangle){
			MoveToEx(hMemDC, Old_xPos, Old_yPos, NULL);
			LineTo(hMemDC, 2 * Old_xPos - xPos, yPos);
			LineTo(hMemDC, xPos, yPos);
			LineTo(hMemDC, Old_xPos, Old_yPos);
			xPos = LOWORD(lParam);
			yPos = HIWORD(lParam);
			LineTo(hMemDC, 2 * Old_xPos - xPos, yPos);
			LineTo(hMemDC, xPos, yPos);
			LineTo(hMemDC, Old_xPos, Old_yPos);
		}
		else if (tRectangle){
			Rectangle(hMemDC, Old_xPos, Old_yPos, xPos, yPos);
		}
		InvalidateRect(hwnd, NULL, FALSE);
		DeleteObject(hBrush);
		DeleteObject(hPen);
		DeleteObject(Old_hBrush);
		DeleteObject(Old_hPen);
		break;
	case WM_MOUSEMOVE:
		if (g_is_clicked){
			hPen = CreatePen(penType, penSize, pColor);		// �� Ÿ��, ����, ����
			Old_hPen = (HPEN)SelectObject(hMemDC, hPen);
			hBrush = CreateSolidBrush(bColor);
			Old_hBrush = (HBRUSH)SelectObject(hMemDC, hBrush);
			SetROP2(hMemDC, R2_NOTXORPEN);
			/*if (pColor == 16777215)
				SetROP2(hMemDC, R2_MERGEPEN);*/
			SelectObject(hMemDC, hPen);
			SelectObject(hMemDC, hBrush);
			if (tBaseLine || tDottedLine){
				MoveToEx(hMemDC, Old_xPos, Old_yPos, NULL);
				LineTo(hMemDC, xPos, yPos);
				xPos = LOWORD(lParam);
				yPos = HIWORD(lParam);
				MoveToEx(hMemDC, Old_xPos, Old_yPos, NULL);
				LineTo(hMemDC, xPos, yPos);

			}
			else if (tFreeLine){
				SetROP2(hMemDC, R2_COPYPEN);
				MoveToEx(hMemDC, Old_xPos, Old_yPos, NULL);
				LineTo(hMemDC, xPos, yPos);
				Old_xPos = xPos;
				Old_yPos = yPos;
				xPos = LOWORD(lParam);
				yPos = HIWORD(lParam);
			}
			else if (tCircle){
				Ellipse(hMemDC, Old_xPos, Old_yPos, xPos, yPos);
				xPos = LOWORD(lParam);
				yPos = HIWORD(lParam);
				Ellipse(hMemDC, Old_xPos, Old_yPos, xPos, yPos);
			}
			else if (tTriangle){
				MoveToEx(hMemDC, Old_xPos, Old_yPos, NULL);
				LineTo(hMemDC, 2 * Old_xPos - xPos, yPos);
				LineTo(hMemDC, xPos, yPos);
				LineTo(hMemDC, Old_xPos, Old_yPos);
				xPos = LOWORD(lParam);
				yPos = HIWORD(lParam);
				LineTo(hMemDC, 2 * Old_xPos - xPos, yPos);
				LineTo(hMemDC, xPos, yPos);
				LineTo(hMemDC, Old_xPos, Old_yPos);
			}
			else if (tRectangle){
				Rectangle(hMemDC, Old_xPos, Old_yPos, xPos, yPos);
				xPos = LOWORD(lParam);
				yPos = HIWORD(lParam);
				Rectangle(hMemDC, Old_xPos, Old_yPos, xPos, yPos);
			}
			InvalidateRect(hwnd, NULL, FALSE);
		}
		DeleteObject(hBrush);
		DeleteObject(hPen);
		DeleteObject(Old_hBrush);
		DeleteObject(Old_hPen);
		break;
	case WM_COMMAND:
		memset(&OFN, 0, sizeof(OPENFILENAME));
		OFN.lStructSize = sizeof(OPENFILENAME);
		OFN.hwndOwner = hwnd;
		OFN.lpstrFilter = L"��Ʈ�� ����(*.bmp)\0*.bmp\0�������(*.*)\0*.*";
		OFN.lpstrFile = lpstrFile;
		OFN.nMaxFileTitle = 50;
		OFN.nMaxFile = 100;
		OFN.lpstrDefExt = TEXT("bmp");
		switch (LOWORD(wParam))
		{
		case ID_LINE_BASELINE:
			KJH.LineBaseLine();
			break;
		case ID_LINE_DOTTEDLINE:
			KJH.LineDottedLine();
			break;
		case ID_LINE_FREELINE:
			KJH.LineFreeLine();
			break;
		case ID_LINE_CIRCLE:
			KJH.LineCircle();
			break;
		case ID_LINE_TRIANGLE:
			KJH.LineTriangle();
			break;
		case ID_LINE_RECTANGLE:
			KJH.LineRectangle();
			break;
		case ID_BRUSH_1MM:
			penSize = 1;
			break;
		case ID_BRUSH_5MM:
			penSize = 5;
			break;
		case ID_BRUSH_10MM:
			penSize = 10;
			break;
		case ID_COLOR_BLACK:
			KJH.Bursh_Color(hwnd, 0, 0, 0);
			break;
		case ID_COLOR_WHITE:
			KJH.Bursh_Color(hwnd, 255, 255, 255);
			break;
		case ID_COLOR_RED:
			KJH.Bursh_Color(hwnd, 255, 0, 0);
			break;
		case ID_COLOR_GREEN:
			KJH.Bursh_Color(hwnd, 0, 255, 0);
			break;
		case ID_COLOR_BLUE:
			KJH.Bursh_Color(hwnd, 0, 0, 255);
			break;
		case ID_COLOR_ADMIN:
			break;
		case ID_BASECOLOR_BLACK:
			KJH.Base_Color(0, 0, 0);
			break;
		case ID_BASECOLOR_WHITE:
			KJH.Base_Color(255, 255, 255);
			break;
		case ID_BASECOLOR_RED:
			KJH.Base_Color(255, 0, 0);
			break;
		case ID_BASECOLOR_GREEN:
			KJH.Base_Color(0, 255, 0);
			break;
		case ID_BASECOLOR_BLUE:
			KJH.Base_Color(0, 0, 255);
			break;
		case ID_BASECOLOR_ADMIN:
			break;
		case ID_40033:			// Create
			break;
		case ID_40034:			// Open
			KJHfile.OpenFile();
			InvalidateRect(hwnd, NULL, TRUE);
			break;
		case ID_40035:			// Save
			KJHfile.SaveFile(hwnd);
			break;
		case ID_40036:			// Close
			DestroyWindow(hwnd);
			break;
		}
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return DefWindowProc(hwnd, iMsg, wParam, lParam);							//	CASE���� ���ǵ��� ���� �޽����� Ŀ���� ó���ϵ��� �޽��� ����
}