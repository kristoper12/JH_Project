#include <Windows.h>
#include "resource.h"
#pragma once
class WinApp
{
protected:
	HINSTANCE m_hInstance;
	int m_exit_state;
public:
	WinApp(HINSTANCE m_hInstance);
	~WinApp();
	void InitApplication();
	void InitInstance();
	void Run();
	int GetExitState() { return m_exit_state; }
};

