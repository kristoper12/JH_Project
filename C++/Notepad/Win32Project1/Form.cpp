#include "WinApp.h"

LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg,
	WPARAM wParam, LPARAM lParam);
LPCTSTR lpszClass = TEXT("201431020_������");

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,			//	WINAPI : ������ ���α׷��̶�� �ǹ�
	LPSTR lpszCmdLine, int nCmdShow)										//	hInstance : �ü���� Ŀ���� ���� ���α׷��� �ο��� ID
{																			//	szCmdLine : Ŀ��Ʈ���� �󿡼� ���α׷� ���� �� ���޵� ���ڿ�
	WNDCLASS WndClass;														//	WndClass ��� ����ü ����									 
	WndClass.style = CS_HREDRAW | CS_VREDRAW;								//	��½�Ÿ�� : ����/������ ��ȭ�� �ٽ� �׸�
	WndClass.lpfnWndProc = (WNDPROC)WndProc;								//	���ν��� �Լ���
	WndClass.cbClsExtra = 0;												//	O/S ��� ���� �޸� (Class)
	WndClass.cbWndExtra = 0;												//	O/s ��� ���� �޸� (Window)
	WndClass.hInstance = hInstance;											//	���� ���α׷� ID
	WndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);						//	������ ����
	WndClass.hCursor = LoadCursor(NULL, IDC_ARROW);							//	Ŀ�� ����
	WndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);			//	����   
	WndClass.lpszMenuName = MAKEINTRESOURCE(IDR_MENU1);						//	�޴� �̸�
	WndClass.lpszClassName = lpszClass;										//	Ŭ���� �̸�
	RegisterClass(&WndClass);												//	�ռ� ������ ������ Ŭ������ �ּ�
	WinApp MyWin(hInstance);

	return MyWin.GetExitState();
}

HDC hdc;

LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	static int check = 0;
	static int line = 1;
	static int count = 1;
	static int xMax, yMax;
	static int xPos, yPos;
	static int scroll_cnt = 0;
	static DWORD dwRead = 0;
	static TCHAR str[100][1000] = { NULL };
	static size_t len = 0;
	static SIZE size;
	static SIZE Scrl_sz;
	static RECT rt;
	int cnt = 0;
	int xInc, yInc;
	TCHAR lpstrFile[100] = { NULL };
	TCHAR Ltemp[1000] = { NULL };
	OPENFILENAME OFN;
	HANDLE fp;
	PAINTSTRUCT ps;
	DWORD dwWrite;
	GetTextExtentPoint(hdc, str[line - 1], 1, &Scrl_sz);

	switch (iMsg) {
	case WM_CREATE:
		GetClientRect(hwnd, &rt);
		xMax = rt.right - rt.left;
		yMax = rt.bottom - rt.top;
		xPos = 0;
		yPos = 0;
		SetScrollRange(hwnd, SB_VERT, 0, yMax, TRUE);
		SetScrollPos(hwnd, SB_VERT, 0, TRUE);
		SetScrollRange(hwnd, SB_HORZ, 0, xMax, TRUE);
		SetScrollPos(hwnd, SB_HORZ, 0, TRUE);
		break;
	case WM_SIZE:
		GetClientRect(hwnd, &rt);
		xMax = rt.right - rt.left;
		yMax = rt.bottom - rt.top;
		break;
	case WM_CHAR:
		switch (wParam) {
		case VK_ESCAPE:
			break;
		case VK_TAB:
			break;
		case VK_BACK: {
			if (len == 0 && line == 1) {								// �� ���� �� ���ʿ��� BackSpace�� �� ��
				check = 0;
				break;
			}
			if (len == 0 && line > 1) {									// �� ������������ �� ������ �ƴ� ��
				if (line == count && str[line - 1][len] == '\0') {		// �ڿ� �ƹ��͵� ���� ��
					len = lstrlen(str[line - 2]);
					line--;
					count--;
				}
				else if (line == count && str[line - 1][len] != '\0') {	// �ڿ��� �ְ� �ؿ��ٿ��� ���� ��
					len = lstrlen(str[line - 2]);
					lstrcat(str[line - 2], str[line - 1]);
					str[line - 1][0] = '\0';
					line--;
					count--;
				}
				else {													// �ؿ��ٿ� ���� ��
					len = lstrlen(str[line - 2]);
					lstrcat(str[line - 2], str[line - 1]);
					line--;
					count--;
					for (int i = line; i < count; i++) {
						lstrcpy(str[i], str[i + 1]);
					}
					str[count][0] = '\0';
				}
			}
			else {														// �Ϲ����� BackSpace �� ��
				if (str[line - 1][len] == '\0') {						// �ڿ� �ƹ��͵� ���� ��
					len--;
					str[line - 1][len] = '\0';
				}
				else {													// �ڿ� ���� ���� ��
					int temp = lstrlen(str[line - 1]);
					for (int i = len; i < temp; i++) {
						str[line - 1][i - 1] = str[line - 1][i];
					}
					str[line - 1][temp - 1] = '\0';
					len--;
				}
			}

			InvalidateRect(hwnd, NULL, TRUE);
			break;
		}
		case VK_RETURN: {
			if (line - yPos / 20 > yMax / 20) {
				yPos += 20;
				ScrollWindow(hwnd, 0, yPos, NULL, NULL);
				SetScrollPos(hwnd, SB_VERT, yPos, TRUE);
			}	
			if (len == lstrlen(str[line - 1])) {							// �� �ڿ� ���� ��
				if (line == count) {										// �ؿ� �ƹ��͵� ���� ��
					len = 0;
					line++;
					count++;
				}
				else {														// �� �ڿ� ��ġ�ϰ� �ؿ� ���� ���� ��
					for (int i = count - 1; i >= line; i--) {
						lstrcpy(str[i + 1], str[i]);
					}
					len = 0;
					str[line][len] = '\0';
					line++;
					count++;
				}
			}
			else {															// �� �ڰ� �ƴ� ��
				if (line == count) {										// �� �ڰ� �ƴϰ� �� �ؿ� ���� ��
					int temp = lstrlen(str[line - 1]);
					for (int i = len; i < temp; i++) {
						str[line][cnt] = str[line - 1][i];
						str[line - 1][i] = '\0';
						cnt++;
					}
					len = 0;
					line++;
					count++;
				}
				else {														// �� �ڰ� �ƴϰ� �� ���� �ƴ� ��
					int temp = lstrlen(str[line - 1]);
					for (int i = count - 1; i >= line; i--) {
						lstrcpy(str[i + 1], str[i]);
					}
					temp = lstrlen(str[line]);
					for (int i = 0; i < temp; i++)
						str[line][i] = '\0';
					temp = lstrlen(str[line - 1]);
					for (int i = len; i < temp; i++) {
						str[line][cnt] = str[line - 1][i];
						str[line - 1][i] = '\0';
						cnt++;
					}
					len = 0;
					line++;
					count++;
				}
			}

			break;
		}
		default: {
			if (str[line - 1][len] == '\0') {
				str[line - 1][len++] = wParam;
			}
			else {
				int temp = lstrlen(str[line - 1]);
				for (int i = temp; i > len; i--) {
					str[line - 1][i] = str[line - 1][i - 1];
				}
				str[line - 1][len++] = (TCHAR)wParam;
			}
			check = 1;
			break;
		}
		}
		hdc = GetDC(hwnd);
		GetTextExtentPoint(hdc, str[line - 1], len, &size);
		ReleaseDC(hwnd, hdc);
		if (str[line - 1][len] == '\0')
			str[line - 1][len] = '\0';
		SetCaretPos(size.cx - xPos, (line - 1) * 20 - yPos);
		InvalidateRect(hwnd, NULL, TRUE);
		break;
	case WM_SETFOCUS:
		CreateCaret(hwnd, NULL, 2, 14);
		ShowCaret(hwnd);
		break;
	case WM_KILLFOCUS:
		HideCaret(hwnd);
		DestroyCaret();
		break;
	case WM_COMMAND:
		memset(&OFN, 0, sizeof(OPENFILENAME));
		OFN.lStructSize = sizeof(OPENFILENAME);
		OFN.hwndOwner = hwnd;
		OFN.lpstrFilter = TEXT("�������(*.*)\0*.*\0");
		OFN.lpstrFile = lpstrFile;
		OFN.nMaxFile = 100;
		switch (LOWORD(wParam))
		{
		case ID_Create:
			if (check == 1) {
				TCHAR LTemp[1024] = { NULL };
				if (MessageBox(hwnd, TEXT("�����Ͻðڽ��ϱ�?"), TEXT("���θ����"), MB_OKCANCEL) == IDOK) {
					if (GetSaveFileName(&OFN) != 0) {
						fp = CreateFile(OFN.lpstrFile, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
						lstrcpy(LTemp, str[0]);
						memset(str[0], '\0', 1024);
						str[0][0] = 0xfeff;
						lstrcat(str[0], LTemp);
						for (int i = 0; i < count; i++) {
							WriteFile(fp, str[i], lstrlen(str[i]) * 2, &dwWrite, NULL);
							WriteFile(fp, "\r", 2, &dwWrite, NULL);
							WriteFile(fp, "\n", 2, &dwWrite, NULL);
						}
					}
				}
				else break;
				for (int i = 0; i < count; i++)
					memset(str[i], '\0', 512);
				len = 0;
				line = 1;
				count = 1;
				InvalidateRect(hwnd, NULL, TRUE);
				GetTextExtentPoint(hdc, str[line - 1], len, &size);
				ReleaseDC(hwnd, hdc);
				SetCaretPos(size.cx + 0, (line - 1) * 20);
				check = 0;
				CloseHandle(fp);
				break;
			}
			else break;
		case ID_Open:
		{
			TCHAR buf[1024] = { NULL };
			char c_buf[1024] = { NULL };
			for (int i = 0; i < count; i++)
				memset(str[i], '\0', 1024);
			count = 1;
			InvalidateRect(hwnd, NULL, TRUE);
			if (GetOpenFileName(&OFN) != 0) {
				dwRead = 1;
				fp = CreateFile(OFN.lpstrFile, GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
				if (fp != INVALID_HANDLE_VALUE) {
					ReadFile(fp, buf, 1024, &dwRead, NULL);
					if (buf[0] == 0xfeff) {
						len = 0;
						for (int i = 0; i < lstrlen(buf); i++) {
							if (buf[i] == '\r');
							else if (buf[i] == '\n') {
								count++;
								len = 0;
							}
							else {
								str[count - 1][len] = buf[i];
								len++;
							}
						}
					}
					else {
						SetFilePointer(fp, 0, NULL, FILE_BEGIN);
						ReadFile(fp, c_buf, 1024, &dwRead, NULL);
						len = 0;
						for (int i = 0; i < strlen(c_buf); i++) {
							if (c_buf[i] == '\r');
							else if (c_buf[i] == '\n') {
								count++;
								len = 0;
							}
							else {
								str[count - 1][len] = c_buf[i];
								len++;
							}
						}
					}
				}
			}
			len = 0;
			line = 0;
			CloseHandle(fp);
			InvalidateRect(hwnd, NULL, TRUE);
			check = 1;
			break;
		}
		case ID_Save: {
			TCHAR LTemp[1024] = { NULL };
			if (GetSaveFileName(&OFN) != 0) {
				fp = CreateFile(OFN.lpstrFile, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
				lstrcpy(LTemp, str[0]);
				memset(str[0], '\0', 1024);
				str[0][0] = 0xfeff;
				lstrcat(str[0], LTemp);
				for (int i = 0; i < count; i++) {
					WriteFile(fp, str[i], lstrlen(str[i]) * 2, &dwWrite, NULL);
					WriteFile(fp, "\r", 2, &dwWrite, NULL);
					WriteFile(fp, "\n", 2, &dwWrite, NULL);
				}
			}
			CloseHandle(fp);
			break;
		}
		case ID_Close:
			if (check == 1) {
				TCHAR LTemp[1024] = { NULL };
				if (MessageBox(hwnd, TEXT("�����Ͻðڽ��ϱ�?"), TEXT("�ݱ�"), MB_YESNOCANCEL) == IDYES) {
					if (GetSaveFileName(&OFN) != 0) {
						fp = CreateFile(OFN.lpstrFile, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
						lstrcpy(LTemp, str[0]);
						memset(str[0], '\0', 1024);
						str[0][0] = 0xfeff;
						lstrcat(str[0], LTemp);
						for (int i = 0; i < count; i++) {
							WriteFile(fp, str[i], lstrlen(str[i]) * 2, &dwWrite, NULL);
							WriteFile(fp, "\r", 2, &dwWrite, NULL);
							WriteFile(fp, "\n", 2, &dwWrite, NULL);
						}
					}
				}
				else {
					break;
				}
			}
			else {
				check = 0;
				DestroyWindow(hwnd);
				break;
			}
			CloseHandle(fp);
			check = 0;
			DestroyWindow(hwnd);
			break;
		}
	case WM_KEYDOWN:
		switch (wParam) {
		case VK_LEFT:
			if (len != 0)
				len--;
			else if (len == 0 && line > 1)
				len = lstrlen(str[--line - 1]);
			break;
		case VK_RIGHT:
			if (len == 0 && str[line - 1][len] == '\0' && line == count)
				break;
			else if (len == lstrlen(str[line - 1])) {
				if (line < count) {
					len = 0;
					line++;
					break;
				}
				else
					break;
			}
			else {
				len++;
				break;
			}
		case VK_UP:
			if (line == 1) {
				break;
			}
			else if (len > lstrlen(str[line - 2])) {						// ���� ĳ���� ��ġ�� ������ ������ Ŭ ���
				len = lstrlen(str[line - 2]);
				line--;
				break;
			}
			else {
				line--;
				break;
			}
		case VK_DOWN:
			if (line == count) {
				break;
			}
			else if (len > lstrlen(str[line])) {							// ���� ĳ���� ��ġ�� ������ ������ Ŭ ���
				len = lstrlen(str[line]);
				line++;
				break;
			}
			else {
				line++;
				break;
			}
		case VK_DELETE:
			if (len == 0 && line == 1)										// �� ���� �� ���ʿ��� Delete�� �� ��
				break;
			else if (len == 0 && str[line - 1][len] == '\0' && line != 1) {	// �� �����̰� �� ������ �ƴ� �� (�� �����ʿ� �ƹ��͵� ����)
				line--;
				len = lstrlen(str[line - 1]);
				count--;
			}
			else {
				if (len == lstrlen(str[line - 1])) {						// �� ������ �� ��
					str[line - 1][len - 1] = '\0';
					len--;
				}
				else {
					int temp = lstrlen(str[line - 1]);
					for (int i = len; i < temp; i++) {
						str[line - 1][i] = str[line - 1][i + 1];
					}
					str[line - 1][temp] = '\0';
				}
			}
			InvalidateRect(hwnd, NULL, TRUE);
			break;
		case VK_HOME:
			len = 0;
			break;
		case VK_END:
			len = lstrlen(str[line - 1]);
			break;
		default:
			break;
		}
		hdc = GetDC(hwnd);
		GetTextExtentPoint(hdc, str[line - 1], len, &size);						// ĳ�� ��ġ ��������
		ReleaseDC(hwnd, hdc);
		SetCaretPos(size.cx + 0 - xPos, (line - 1) * 20 - yPos);
		break;
	case WM_HSCROLL:															// ����
		xInc = 0;
		GetTextExtentPoint(hdc, str[line - 1], len, &size);
		switch (LOWORD(wParam)) {												
		case SB_LINELEFT:														// ���� ��ư Ŭ��
			xInc = -Scrl_sz.cx;
			if (scroll_cnt > 0)
				scroll_cnt--;													
			break;
		case SB_LINERIGHT:														// ������ ��ư Ŭ��
			xInc = Scrl_sz.cx;													
			if (scroll_cnt != 768)
				scroll_cnt++;
			break;																
		case SB_PAGELEFT:														// ���� ���� Ŭ��
			xInc = -20;
			break;
		case SB_PAGERIGHT:														// ������ ���� Ŭ��
			xInc = 20;
			break;
		case SB_THUMBTRACK:														// ��ũ���� �巡�� ��
			xInc = HIWORD(wParam) - xPos;
			break;
		}
		if (xPos + xInc < 0)
			xInc = -xPos;
		if (xPos + xInc > xMax)
			xInc = xMax - xPos;
		xPos += xInc;
		ScrollWindow(hwnd, -xInc, 0, NULL, NULL);
		SetScrollPos(hwnd, SB_HORZ, xPos, TRUE);
		return 0;
	case WM_VSCROLL:															// ����
		yInc = 0;
		switch (LOWORD(wParam)) {
		case SB_LINEUP:															// �� ��ư Ŭ��
			yInc = -20;
			break;
		case SB_LINEDOWN:														// �Ʒ� ��ư Ŭ��
			yInc = 20;
			break;
		case SB_PAGEUP:															// �� ���� Ŭ��
			yInc = -40;
			break;
		case SB_PAGEDOWN:														// �Ʒ� ���� Ŭ��
			yInc = 40;
			break;
		case SB_THUMBTRACK:														// ��ũ���� �巡�� ��
			yInc = HIWORD(wParam) - yPos;
			break;
		}
		if (yPos + yInc < 0)
			yInc = -yPos;
		if (yPos + yInc > yMax)
			yInc = yMax - yPos;
		yPos += yInc;
		ScrollWindow(hwnd, 0, -yInc, NULL, NULL);
		SetScrollPos(hwnd, SB_VERT, yPos, TRUE);
		return 0;
	case WM_MOUSEWHEEL:
		if ((short)HIWORD(wParam) < 0)											// WM_MOUSEWHEEL �޽��� �� �� wParam �� ���� ������ �Ÿ�
			SendMessage(														// Ư�� �������� �ڵ鿡 �޽����� �����ϴ� �Լ�
				hwnd,															// �޽����� ���޹��� ������ �ڵ�
				WM_VSCROLL,														// ������ �޽���
				MAKELONG(SB_LINEDOWN, 0),										// wParam
				0);																// lParam
		else
			SendMessage(hwnd, WM_VSCROLL, MAKELONG(SB_LINEUP, 0), 0);
		return 0;

	case WM_PAINT: {
		hdc = BeginPaint(hwnd, &ps);
		for (int i = 0; i < count; i++)
			TextOut(hdc, 1 - xPos, i * 20 - yPos, str[i], lstrlen(str[i]));

		EndPaint(hwnd, &ps);
		break;
	}
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return DefWindowProc(hwnd, iMsg, wParam, lParam);							//	CASE���� ���ǵ��� ���� �޽����� Ŀ���� ó���ϵ��� �޽��� ����
}