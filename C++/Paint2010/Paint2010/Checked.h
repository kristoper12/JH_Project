#include <Windows.h>
#pragma once

extern HDC hdc;
extern HDC hMemDC;
extern HANDLE hFile;
extern HBITMAP hBitmap, Old_hBitmap;
extern int g_is_clicked;
extern int penType;
extern int penSize;
extern int cnt;
extern HBRUSH hBrush;
extern HBRUSH Old_hBrush;
extern HPEN hPen;
extern HPEN Old_hPen;
extern COLORREF pColor;
extern COLORREF bColor;
extern BOOL tBaseLine;
extern BOOL tFreeLine;
extern BOOL tDottedLine;
extern BOOL tCircle;
extern BOOL tTriangle;
extern BOOL tRectangle;
extern BOOL FileCheck;
extern RECT crt;
extern OPENFILENAME OFN;
extern TCHAR lpstrFile[100];
extern DWORD dwRead;
extern BITMAPFILEHEADER fh;
extern BITMAPINFOHEADER ih;
extern RGBQUAD rgb[256];
extern BYTE *pData;
extern DWORD dwDataSize;
extern DWORD dwPitch;
extern DWORD dwAddr;
class Checked
{
public:
	Checked();
	~Checked();
	void Bursh_Color(HWND hwnd, int R, int G, int B) { pColor = RGB(R, G, B); }
	void Base_Color(int R, int G, int B) { bColor = RGB(R, G, B); }
	void LineBaseLine();
	void LineDottedLine();
	void LineFreeLine();
	void LineCircle();
	void LineTriangle();
	void LineRectangle();
};

