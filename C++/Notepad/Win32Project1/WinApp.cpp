#include "WinApp.h"

WinApp::WinApp(HINSTANCE a_hInstance)
{
	m_hInstance = a_hInstance;
	InitInstance();
	Run();
}
WinApp::~WinApp()
{

}
//void WinApp::InitApplication() {
//
//	WNDCLASS WndClass;											 //	WndClass ��� ����ü ����									 
//	WndClass.style = CS_HREDRAW | CS_VREDRAW;					 //	��½�Ÿ�� : ����/������ ��ȭ�� �ٽ� �׸�
//	WndClass.lpfnWndProc = (WNDPROC)WndProc;					 //	���ν��� �Լ���
//	WndClass.cbClsExtra = 0;									 //	O/S ��� ���� �޸� (Class)
//	WndClass.cbWndExtra = 0;									 //	O/s ��� ���� �޸� (Window)
//	WndClass.hInstance = m_hInstance;							 //	���� ���α׷� ID
//	WndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);			 //	������ ����
//	WndClass.hCursor = LoadCursor(NULL, IDC_ARROW);				 //	Ŀ�� ����
//	WndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);//	����   
//	WndClass.lpszMenuName = MAKEINTRESOURCE(IDR_MENU1);			 //	�޴� �̸�
//	WndClass.lpszClassName = lpszClass;							 //	Ŭ���� �̸�
//	RegisterClass(&WndClass);									 //	�ռ� ������ ������ Ŭ������ �ּ�
//}
void WinApp::InitInstance() {
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
		m_hInstance,    										 //	���� ���α׷� ID
		NULL     												 //	������ ������ ����
	);
	ShowWindow(hwnd, SW_SHOW);									 //	�������� ȭ�� ���
	UpdateWindow(hwnd);											 //	O/S �� WM_PAINT �޽��� ����
}
void WinApp::Run() {
	MSG		msg;
	while (GetMessage(&msg, NULL, 0, 0))						 //	WinProc()���� PostQuitMessage() ȣ�� ������ ó��
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);									 //	WinMain -> WinProc  
	}
	m_exit_state = msg.wParam;
}