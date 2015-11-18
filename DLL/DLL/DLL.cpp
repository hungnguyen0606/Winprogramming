// DLL.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"

#define EXPORT  __declspec(dllexport)

HWND win;
HHOOK hHook = NULL;
HHOOK hm = NULL;
HINSTANCE hinstLib;
bool isshow = true;
int last = -1;
LRESULT CALLBACK MouseProc(int nCode, WPARAM wParam, LPARAM lParam)
{
	if (nCode < 0) // không xử lý message 
		return CallNextHookEx(hHook, nCode, wParam, lParam);
	EVENTMSG *tmp = (EVENTMSG*)lParam;
	int u = GetKeyState(VK_CONTROL);
	if (wParam == WM_RBUTTONDOWN)
		if (u < 0)
		{
			last = 0;
			if (isshow)
			{
				ShowWindow(win, SW_HIDE);
				//MessageBox(NULL, L"HIDE", L"KeyboardHook", MB_OK);
			}
			else
			{
				ShowWindow(win, SW_SHOWMAXIMIZED);
				RECT t;
				GetClientRect(win, &t);
				SystemParametersInfo(SPI_GETWORKAREA, 0, &t, 0);
				int hei = GetSystemMetrics(SM_CYFULLSCREEN);
				int wid = GetSystemMetrics(SM_CXFULLSCREEN);
				SetWindowPos(win, HWND_TOPMOST, 0, 0, t.right, t.bottom, SWP_SHOWWINDOW);
				//MessageBox(NULL, L"SHOW", L"KeyboardHook", MB_OK);
			}
				
			isshow = !isshow;
			//MessageBox(NULL, L"SHOW", L"KeyboardHook", MB_OK);
		}
	return CallNextHookEx(hm, nCode, wParam, lParam);

}
LRESULT CALLBACK KeyboardProc(int nCode, WPARAM wParam, LPARAM lParam) 
{
	if (nCode < 0) // không xử lý message 
		return CallNextHookEx(hHook, nCode, wParam, lParam);
	// xử lý messagedd\\
	TCHAR szBuf[128];
	
	if (wParam == VK_CONTROL)
		last = 1;

	return CallNextHookEx(hHook, nCode, wParam, lParam);
}

EXPORT void _doInstallHook(HWND hWnd)
{
	if (hHook!=NULL) return;
	win = hWnd;
	hm = SetWindowsHookEx(WH_MOUSE_LL, (HOOKPROC)MouseProc, hinstLib, 0);
	hHook = SetWindowsHookEx(WH_KEYBOARD, (HOOKPROC) KeyboardProc, hinstLib, 0);
	if (hHook)
		MessageBox(hWnd, L"Setup hook successfully", L"Result", MB_OK);
	else
		MessageBox(hWnd, L"Setup hook fail", L"Result", MB_OK);
	
}

EXPORT void _doRemoveHook(HWND hWnd)
{
	if (hHook==NULL) return;
	UnhookWindowsHookEx(hm);
	UnhookWindowsHookEx(hHook);
	hHook = NULL;
	MessageBox(hWnd, L"Remove hook successfully", L"Result", MB_OK);
}