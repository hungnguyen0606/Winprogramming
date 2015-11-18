
#pragma once
#include "stdafx.h"
#include "H.3.1.h"

INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);
class allmenu
{
	static HMENU menu[2];
	static int currentMenu;

	static LRESULT CALLBACK menu1Proc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam, int wmId,
		int wmEvent, PAINTSTRUCT &ps, HINSTANCE &hInst, HDC& hdc);
	static LRESULT CALLBACK menu2Proc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam, int wmId,
		int wmEvent, PAINTSTRUCT &ps, HINSTANCE &hInst, HDC& hdc); 

	static void initMenu1();
	static void initMenu2();
public:
	
	HMENU& operator() (int i)
	{
		return menu[i];
	}

	static LRESULT CALLBACK menuProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam, int wmId,
		int wmEvent, PAINTSTRUCT &ps, HINSTANCE &hInst, HDC& hdc);
};





LRESULT CALLBACK menuProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam, int wmId,
	int wmEvent, PAINTSTRUCT &ps, HINSTANCE &hInst, HDC& hdc);
