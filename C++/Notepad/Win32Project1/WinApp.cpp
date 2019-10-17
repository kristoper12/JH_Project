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
//	WNDCLASS WndClass;											 //	WndClass 라는 구조체 정의									 
//	WndClass.style = CS_HREDRAW | CS_VREDRAW;					 //	출력스타일 : 수직/수평의 변화시 다시 그림
//	WndClass.lpfnWndProc = (WNDPROC)WndProc;					 //	프로시저 함수명
//	WndClass.cbClsExtra = 0;									 //	O/S 사용 여분 메모리 (Class)
//	WndClass.cbWndExtra = 0;									 //	O/s 사용 여분 메모리 (Window)
//	WndClass.hInstance = m_hInstance;							 //	응용 프로그램 ID
//	WndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);			 //	아이콘 유형
//	WndClass.hCursor = LoadCursor(NULL, IDC_ARROW);				 //	커서 유형
//	WndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);//	배경색   
//	WndClass.lpszMenuName = MAKEINTRESOURCE(IDR_MENU1);			 //	메뉴 이름
//	WndClass.lpszClassName = lpszClass;							 //	클래스 이름
//	RegisterClass(&WndClass);									 //	앞서 정의한 윈도우 클래스의 주소
//}
void WinApp::InitInstance() {
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
		m_hInstance,    										 //	응용 프로그램 ID
		NULL     												 //	생성된 윈도우 정보
	);
	ShowWindow(hwnd, SW_SHOW);									 //	윈도우의 화면 출력
	UpdateWindow(hwnd);											 //	O/S 에 WM_PAINT 메시지 전송
}
void WinApp::Run() {
	MSG		msg;
	while (GetMessage(&msg, NULL, 0, 0))						 //	WinProc()에서 PostQuitMessage() 호출 때까지 처리
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);									 //	WinMain -> WinProc  
	}
	m_exit_state = msg.wParam;
}