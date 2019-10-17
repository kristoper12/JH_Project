#include "Checked.h"
#include "File.h"
#include "resource.h"
#define MAX_COUNT 1000

LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam);
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,			//	WINAPI : 윈도우 프로그램이라는 의미
	LPSTR lpszCmdLine, int nCmdShow)										//	hInstance : 운영체제의 커널이 응용 프로그램에 부여한 ID
{																			//	szCmdLine : 커멘트라인 상에서 프로그램 구동 시 전달된 문자열
	WNDCLASS WndClass;											 //	WndClass 라는 구조체 정의									 
	WndClass.style = CS_HREDRAW | CS_VREDRAW;					 //	출력스타일 : 수직/수평의 변화시 다시 그림
	WndClass.lpfnWndProc = (WNDPROC)WndProc;					 //	프로시저 함수명
	WndClass.cbClsExtra = 0;									 //	O/S 사용 여분 메모리 (Class)
	WndClass.cbWndExtra = 0;									 //	O/s 사용 여분 메모리 (Window)
	WndClass.hInstance = hInstance;								 //	응용 프로그램 ID
	WndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);			 //	아이콘 유형
	WndClass.hCursor = LoadCursor(NULL, IDC_ARROW);				 //	커서 유형
	WndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);//	배경색   
	WndClass.lpszMenuName = MAKEINTRESOURCE(IDR_MENU1);			 //	메뉴 이름
	WndClass.lpszClassName = L"201431020_김진혁";				 //	클래스 이름
	RegisterClass(&WndClass);									 //	앞서 정의한 윈도우 클래스의 주소
	HWND	hwnd;												 //	iCmdShow : 윈도우가 화면에 출력될 형태
	hwnd = CreateWindow(L"201431020_김진혁",					 //	윈도우가 생성되면 핸들(hwnd)이 반환
		L"201431020_김진혁",									 //	윈도우 클래스, 타이틀 이름
		WS_OVERLAPPEDWINDOW,									 //	윈도우 스타일
		CW_USEDEFAULT,											 //	윈도우 위치, x좌표
		CW_USEDEFAULT,											 //	윈도우 위치, y좌표
		CW_USEDEFAULT,											 //	윈도우 폭   
		CW_USEDEFAULT,											 //	윈도우 높이   
		// CW_USEDEFAULT
		NULL,													 //	부모 윈도우 핸들	 
		NULL,													 //	메뉴 핸들
		hInstance,    											 //	응용 프로그램 ID
		NULL     												 //	생성된 윈도우 정보
		);
	ShowWindow(hwnd, SW_SHOW);									 //	윈도우의 화면 출력
	UpdateWindow(hwnd);											 //	O/S 에 WM_PAINT 메시지 전송
	MSG		msg;
	while (GetMessage(&msg, NULL, 0, 0))						 //	WinProc()에서 PostQuitMessage() 호출 때까지 처리
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
		hPen = CreatePen(penType, penSize, pColor);		// 선 타입, 굵기, 색깔
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
			hPen = CreatePen(penType, penSize, pColor);		// 선 타입, 굵기, 색깔
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
		OFN.lpstrFilter = L"비트맵 파일(*.bmp)\0*.bmp\0모든파일(*.*)\0*.*";
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
	return DefWindowProc(hwnd, iMsg, wParam, lParam);							//	CASE에서 정의되지 않은 메시지는 커널이 처리하도록 메시지 전달
}