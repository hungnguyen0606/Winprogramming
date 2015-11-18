// DLL_SHOW.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include "DLL_SHOW.h"

bool isshow = true;
HHOOK hHook;
HINSTANCE hinstlib;
HWND mainWindow, textWindow, drawWindow, dlgShape;
// This is an example of an exported variable
DLL_SHOW_API int nDLL_SHOW=0;

// This is an example of an exported function.
DLL_SHOW_API int fnDLL_SHOW(void)
{
	return 42;
}

// This is the constructor of a class that has been exported.
// see DLL_SHOW.h for the class definition
CDLL_SHOW::CDLL_SHOW()
{
	return;
}

DLL_SHOW_API void showAllWindow(UINT type)
{
	RECT t;
	ShowWindow(textWindow, SW_HIDE);
	ShowWindow(drawWindow, SW_HIDE);
	SystemParametersInfo(SPI_GETWORKAREA, 0, &t, 0);
	int wid = (t.right - t.left) / 20;
	int hei = (t.bottom - t.top) / 10;
	

	RECT dlg;
	GetClientRect(dlgShape, &dlg);
	int dlgwid = dlg.right - dlg.left;
	int dlghei = dlg.bottom - dlg.top;
	
	
	HRGN text = CreateRoundRectRgn(0, 0, wid * 8, hei * 8, wid/3, hei/3);
	//GetWindowRgn(textWindow, text);
	HRGN draw = CreateRoundRectRgn(0, 0, wid * 8, hei * 8, wid / 3, hei / 3);
	//HRGN dlgrect = CreateRoundRectRgn(0, 0, dlgwid, dlghei, dlgwid / 3, dlghei / 3);
	SetWindowRgn(textWindow, text, true);
	SetWindowRgn(drawWindow, draw, true);
	//SetWindowRgn(dlgShape, dlgrect, true);

	SetWindowPos(dlgShape, HWND_TOPMOST, 19 * wid - dlgwid, hei / 2 - dlghei / 2, dlgwid, dlghei, type);
	SetWindowPos(textWindow, HWND_TOPMOST, wid, hei, wid * 8, hei * 8, type);
	SetWindowPos(drawWindow, HWND_TOPMOST, 11 * wid, hei, wid * 8, hei * 8, type);
	//SetWindowRgn(drawWindow, draw, true);
	
	//TCHAR s[1111];
	
	//wsprintf(s, "%d %d %d %d", wid, hei, )
}

LRESULT CALLBACK hookShow(int nCode, WPARAM wParam, LPARAM lParam)
{
	if (nCode < 0) // không xử lý message 
		return CallNextHookEx(hHook, nCode, wParam, lParam);

	int u = GetKeyState(VK_CONTROL);
	if (wParam == WM_RBUTTONDOWN)
		if (u < 0)
		{
			if (isshow)
			{
				showAllWindow(SWP_HIDEWINDOW);
				//MessageBox(NULL, L"HIDE", L"KeyboardHook", MB_OK);
			}
			else
			{
				showAllWindow(SWP_SHOWWINDOW);
				
			}

			isshow = !isshow;
			//MessageBox(NULL, L"SHOW", L"KeyboardHook", MB_OK);
		}
	return CallNextHookEx(hHook, nCode, wParam, lParam);

}

DLL_SHOW_API void setHook(HWND mainWin, HWND textWin, HWND drawWin, HWND dlgshape)
{
	mainWindow = mainWin;
	textWindow = textWin;
	drawWindow = drawWin;
	dlgShape = dlgshape;

	hHook = SetWindowsHookEx(WH_MOUSE_LL, hookShow, hinstlib, 0);
}

DLL_SHOW_API void unHook()
{
	UnhookWindowsHookEx(hHook);
}
