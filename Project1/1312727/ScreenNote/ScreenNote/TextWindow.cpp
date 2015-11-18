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
	wcex.hIcon = 0;
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_APPWORKSPACE + 1);
	wcex.lpszMenuName = 0;
	wcex.lpszClassName = L"TEXT_WINDOW";
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
	
	switch (message)
	{
	case WM_COMMAND:
		wmId = LOWORD(wParam);
		wmEvent = HIWORD(wParam);
		// Parse the menu selections:
		switch (wmId)
		{
		
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
		break;

	
	case WM_CREATE:
	{
		//TCHAR title[50];
		//_stprintf_p(title, 50, L"Text %d", cwindow);
		RECT rect;
		GetClientRect(hWnd, &rect);
		hWndTextWin = CreateWindow(L"Edit", L"HELLO", WS_CHILD | WS_VISIBLE | ES_MULTILINE ,
			0, 0, (rect.right - rect.left), (rect.bottom - rect.top), hWnd, NULL, 0, NULL);
		
		/*SetWindowLong(hWnd, 0, (LONG) &hWndTextWin);*/
		COLORREF *color = new COLORREF();
		*color = RGB(0, 0, 0);
		SetWindowLong(hWnd, 0, (LONG)color);
	
		return DefWindowProc(hWnd, message, wParam, lParam);
	}

	case WM_SIZE:
	{
		UINT w = LOWORD(lParam);
		UINT h = HIWORD(lParam);
		MoveWindow(hWndTextWin, 0, 0, w, h, false);
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		// TODO: Add any drawing code here...
		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		delete (COLORREF*)GetWindowLong(hWnd, 0);
		return DefWindowProc(hWnd, message, wParam, lParam);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}