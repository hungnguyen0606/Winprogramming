#include "stdafx.h"
#include "Resource.h"
#include "TextWindow.h"
#include "Global.h"



ATOM myTextWindow::MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style = CS_HREDRAW | CS_VREDRAW ;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 12;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_H51));
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_APPWORKSPACE + 1);
	wcex.lpszMenuName = MAKEINTRESOURCE(IDC_H51);
	wcex.lpszClassName = L"MDI_TEXT_CHILD";
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));
	if (RegisterClassEx(&wcex))
		return TRUE;
	return FALSE;
	return RegisterClassEx(&wcex);
}

LRESULT CALLBACK	myTextWindow::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	static int cwindow = 0;
	int wmId, wmEvent;
	PAINTSTRUCT ps;
	HDC hdc;
	static HWND hWndTextWin;
	hWndFrame hwndFrame;
	switch (message)
	{
	case WM_COMMAND:
		wmId = LOWORD(wParam);
		wmEvent = HIWORD(wParam);
		// Parse the menu selections:
		switch (wmId)
		{
		
		default:
			return DefMDIChildProc(hWnd, message, wParam, lParam);
		}
		break;

	case WM_CTLCOLOREDIT:
	{
		HDC tmp = (HDC)wParam;
		HWND edc = (HWND)lParam;
		HGDIOBJ pen = GetStockObject(DC_PEN);
		SetTextColor(tmp, *((COLORREF*)GetWindowLong(hWnd, 0)));
		//SelectObject(tmp, pen);
		//GetWindowLong()
		//COLORREF co = 
		SetDCPenColor(tmp, RGB(255,255,255));
		//return DefMDIChildProc(hWnd, message, wParam, lParam);
		return (LRESULT)pen;
	}
	case WM_SETFONT:
	{
		SendMessage(hWndTextWin, WM_SETFONT, wParam, lParam);
		return DefMDIChildProc(hWnd, message, wParam, lParam);
	}
	case WM_CREATE:
	{
		//TCHAR title[50];
		//_stprintf_p(title, 50, L"Text %d", cwindow);
		RECT rect;
		GetClientRect(hWnd, &rect);
		hWndTextWin = CreateWindow(L"Edit", L"HELLO", WS_CHILD | WS_VISIBLE | WS_VSCROLL | ES_MULTILINE ,
			0, 0, (rect.right - rect.left), (rect.bottom - rect.top), hWnd, NULL, 0, NULL);
		
		/*SetWindowLong(hWnd, 0, (LONG) &hWndTextWin);*/
		COLORREF *color = new COLORREF();
		*color = RGB(0, 0, 0);
		SetWindowLong(hWnd, 0, (LONG)color);
	
		return DefMDIChildProc(hWnd, message, wParam, lParam);
	}

	//case WM_SETFOCUS:
	//{

	//	HMENU mymenu = GetMenu(hwndFrame());
	//	EnableMenuItem(mymenu, ID_EDIT_CUT, MF_BYCOMMAND | MF_ENABLED);
	//	EnableMenuItem(mymenu, ID_EDIT_COPY, MF_BYCOMMAND | MF_ENABLED);
	//	EnableMenuItem(mymenu, ID_EDIT_PASTE, MF_BYCOMMAND | MF_ENABLED);
	//	EnableMenuItem(mymenu, ID_EDIT_SELECTALL, MF_BYCOMMAND | MF_ENABLED);
	//	EnableMenuItem(mymenu, ID_FORMAT_CHOOSEFONT, MF_BYCOMMAND | MF_ENABLED);

	//	/*EnableMenuItem(mymenu, ID_DRAW_PIXEL, MF_BYCOMMAND | MF_GRAYED);
	//	EnableMenuItem(mymenu, ID_DRAW_RECTANGLE, MF_BYCOMMAND | MF_GRAYED);
	//	EnableMenuItem(mymenu, ID_DRAW_ELLIPSE, MF_BYCOMMAND | MF_GRAYED);
	//	EnableMenuItem(mymenu, ID_DRAW_LINE, MF_BYCOMMAND | MF_GRAYED);*/
	//	return DefMDIChildProc(hWnd, message, wParam, lParam);
	//}
	//

	//case WM_KILLFOCUS:
	//{
	//	HMENU mymenu = GetMenu(hwndFrame());
	//	EnableMenuItem(mymenu, ID_EDIT_CUT, MF_BYCOMMAND | MF_GRAYED);
	//	EnableMenuItem(mymenu, ID_EDIT_COPY, MF_BYCOMMAND | MF_GRAYED);
	//	EnableMenuItem(mymenu, ID_EDIT_PASTE, MF_BYCOMMAND | MF_GRAYED);
	//	EnableMenuItem(mymenu, ID_EDIT_SELECTALL, MF_BYCOMMAND | MF_GRAYED);
	//	EnableMenuItem(mymenu, ID_FORMAT_CHOOSEFONT, MF_BYCOMMAND | MF_GRAYED);
	//	return DefMDIChildProc(hWnd, message, wParam, lParam);
	//}
	case WM_SIZE:
	{
		UINT w = LOWORD(lParam);
		UINT h = HIWORD(lParam);
		MoveWindow(hWndTextWin, 0, 0, w, h, false);
		return DefMDIChildProc(hWnd, message, wParam, lParam);
	}
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		// TODO: Add any drawing code here...
		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY:
		//PostQuitMessage(0);
		delete (COLORREF*)GetWindowLong(hWnd, 0);
		return DefMDIChildProc(hWnd, message, wParam, lParam);
		break;
	default:
		return DefMDIChildProc(hWnd, message, wParam, lParam);
	}
	return 0;
}