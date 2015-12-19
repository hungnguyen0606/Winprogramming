// H12.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "H12.h"

#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;								// current instance
TCHAR szTitle[MAX_LOADSTRING];					// The title bar text
TCHAR szWindowClass[MAX_LOADSTRING];			// the main window class name

// Forward declarations of functions included in this code module:
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	About(HWND, UINT, WPARAM, LPARAM);

char* pasteAnsiText(HWND hWnd);
TCHAR* pasteUnicodeText(HWND hWnd);
HBITMAP pasteBitmap(HWND hWnd);

int APIENTRY _tWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPTSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

 	// TODO: Place code here.
	MSG msg;
	HACCEL hAccelTable;

	// Initialize global strings
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_H12, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// Perform application initialization:
	if (!InitInstance (hInstance, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_H12));

	// Main message loop:
	while (GetMessage(&msg, NULL, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return (int) msg.wParam;
}



//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_H12));
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= MAKEINTRESOURCE(IDC_H12);
	wcex.lpszClassName	= szWindowClass;
	wcex.hIconSm		= LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassEx(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   HWND hWnd;

   hInst = hInstance; // Store instance handle in our global variable

   hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, hInstance, NULL);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE:  Processes messages for the main window.
//
//  WM_COMMAND	- process the application menu
//  WM_PAINT	- Paint the main window
//  WM_DESTROY	- post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	PAINTSTRUCT ps;
	HDC hdc;
	static HBITMAP def = NULL;
	switch (message)
	{
	case WM_COMMAND:
		wmId    = LOWORD(wParam);
		wmEvent = HIWORD(wParam);
		// Parse the menu selections:
		switch (wmId)
		{
		case IDM_ABOUT:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			break;
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
		case ID_PASTE_PASTEANSITEXT:
		{
		
			InvalidateRect(hWnd, 0, TRUE);
			UpdateWindow(hWnd);
			
			hdc = GetDC(hWnd);
			char* t = pasteAnsiText(hWnd);
			if (t == NULL)
			{
				MessageBox(hWnd, L"Clipboard's content isn't ansi text", L"ERROR", MB_OK);
				break;
			}
			TCHAR* temp = new TCHAR[strlen(t) + 1];
			for (int i = 0; i < strlen(t); ++i)
				temp[i] = TCHAR(t[i]);
			temp[strlen(t)] = 0;
			RECT a;
			GetClientRect(hWnd, &a);
			DrawText(hdc, temp, strlen(t), &a, DT_LEFT | DT_WORDBREAK);
			delete temp;
			delete t;
			
			ReleaseDC(hWnd, hdc);
			break;
		}
		case ID_PASTE_PASTEUNICODETEXT:
		{
			InvalidateRect(hWnd, 0, TRUE);
			UpdateWindow(hWnd);
			hdc = GetDC(hWnd);
			TCHAR* t = pasteUnicodeText(hWnd);
			if (t == NULL)
			{
				MessageBox(hWnd, L"Clipboard's content isn't unicode text", L"ERROR", MB_OK);
				break;
			}

			RECT a;
			GetClientRect(hWnd, &a);
			DrawText(hdc, t, lstrlen(t), &a, DT_LEFT | DT_WORDBREAK);
			break;
		}
		case ID_PASTE_PASTEBITMAP:
		{
			InvalidateRect(hWnd, 0, TRUE);
			UpdateWindow(hWnd);
			hdc = GetDC(hWnd);

			HBITMAP img = pasteBitmap(hWnd);
			if (img == NULL)
			{
				MessageBox(hWnd, L"Clipboard's content isn't bitmap", L"ERROR", MB_OK);
				break;
			}
			def = img;

			HDC memDC = CreateCompatibleDC(hdc);
			HBITMAP hOldbmp = (HBITMAP)SelectObject(memDC, img);

			BITMAP bm;
			GetObject(img, sizeof(BITMAP), &bm);

			BitBlt(hdc, 0, 0, bm.bmWidth, bm.bmHeight, memDC, 0, 0, SRCCOPY);

			SelectObject(memDC, hOldbmp);
			DeleteDC(memDC);

			ReleaseDC(hWnd, hdc);
			break;
		}
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
		break;
	case WM_PAINT:
	{
		if (def == NULL)
			break;
		hdc = BeginPaint(hWnd, &ps);
		// TODO: Add any drawing code here...
		HBITMAP img = def;
		if (img == NULL)
		{
			MessageBox(hWnd, L"Clipboard's content isn't bitmap", L"ERROR", MB_OK);
			break;
		}

		HDC memDC = CreateCompatibleDC(hdc);
		HBITMAP hOldbmp = (HBITMAP)SelectObject(memDC, img);

		BITMAP bm;
		GetObject(img, sizeof(BITMAP), &bm);

		BitBlt(hdc, 0, 0, bm.bmWidth, bm.bmHeight, memDC, 0, 0, SRCCOPY);

		SelectObject(memDC, hOldbmp);
		DeleteDC(memDC);
		EndPaint(hWnd, &ps);
		break;
	}
		
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

// Message handler for about box.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}

char* pasteAnsiText(HWND hWnd)
{
	char* szText = NULL;
	if (OpenClipboard(hWnd))
	{
		HANDLE hData = GetClipboardData(CF_TEXT);
		if (hData != NULL)
		{
			char* pData = (char*)GlobalLock(hData);
			szText = new char[strlen(pData) + 1];
			strcpy(szText, pData);
			GlobalUnlock(hData);
		}
		CloseClipboard();
	}
	return szText;
}

TCHAR* pasteUnicodeText(HWND hWnd)
{
	TCHAR* szText = NULL;
	if (OpenClipboard(hWnd))
	{
		HANDLE hData = GetClipboardData(CF_UNICODETEXT);
		if (hData != NULL)
		{ 
			
			TCHAR* pData = (TCHAR*)GlobalLock(hData);
			szText = new TCHAR[lstrlen(pData) + 1];
			lstrcpy(szText, pData);
			GlobalUnlock(hData);
		}
		CloseClipboard();
	}
	return szText;
}

HBITMAP pasteBitmap(HWND hWnd)
{
	HBITMAP ret = NULL;
	if (OpenClipboard(hWnd))
	{
		HBITMAP hData = (HBITMAP) GetClipboardData(CF_BITMAP);
		if (hData != NULL)
		{
			BITMAP bm;
			GetObject(hData, sizeof(BITMAP), &bm);
			ret = (HBITMAP)CopyImage(hData, IMAGE_BITMAP, bm.bmWidth, bm.bmHeight, LR_DEFAULTSIZE);
			//szText = new char[strlen(pData) + 1];
			//strcpy(szText, pData);
			GlobalUnlock(hData);
		}
		CloseClipboard();
	}
	return ret;	//return szText;
}