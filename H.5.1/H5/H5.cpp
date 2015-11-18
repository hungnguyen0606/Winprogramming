// H5.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "H5.h"

#define MAX_LOADSTRING 100
#define WINDOW_MENU_POS 4
// Global Variables:
HINSTANCE hInst;								// current instance
TCHAR szTitle[MAX_LOADSTRING];					// The title bar text
TCHAR szWindowClass[MAX_LOADSTRING];			// the main window class name

// Forward declarations of functions included in this code module:
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	About(HWND, UINT, WPARAM, LPARAM);

HWND hWndMDIClient, hWndFrame;

ATOM MyRegisterClassDRAWWINDOW(HINSTANCE hInstance);

ATOM MyRegisterClassTEXTWINDOW(HINSTANCE hInstance);
LRESULT CALLBACK WndProcText(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK	WndProcDraw(HWND, UINT, WPARAM, LPARAM);
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
	LoadString(hInstance, IDC_H5, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);
	MyRegisterClassDRAWWINDOW(hInstance);
	MyRegisterClassTEXTWINDOW(hInstance);
	// Perform application initialization:
	if (!InitInstance (hInstance, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_H5));

	// Main message loop:
	while (GetMessage(&msg, NULL, 0, 0))
	{
		if (!TranslateMDISysAccel(hWndMDIClient, &msg) &&
			
		!TranslateAccelerator(hWndFrame, hAccelTable, &msg))
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
	wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_H5));
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_APPWORKSPACE + 1);
	wcex.lpszMenuName	= MAKEINTRESOURCE(IDC_H5);
	wcex.lpszClassName	= szWindowClass;
	wcex.hIconSm		= LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));
	/*if (RegisterClassEx(&wcex))
		return true;
	return false;*/
	return RegisterClassEx(&wcex);
}

ATOM MyRegisterClassDRAWWINDOW(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProcDraw;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_H5));
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = MAKEINTRESOURCE(IDC_H5);
	wcex.lpszClassName = L"MDI_DRAWWINDOW_CHILD";
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));
	bool temp = RegisterClassEx(&wcex);
	return temp;
}

ATOM MyRegisterClassTEXTWINDOW(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProcText;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_H5));
	wcex.hCursor = LoadCursor(NULL, IDC_CROSS);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = MAKEINTRESOURCE(IDC_H5);
	wcex.lpszClassName = L"MDI_TEXTWINDOW_CHILD";
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));
	bool temp = RegisterClassEx(&wcex);
	return temp;
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

   hWndFrame = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, hInstance, NULL);

   if (!hWndFrame)
   {
      return FALSE;
   }

   ShowWindow(hWndFrame, nCmdShow);
   UpdateWindow(hWndFrame);

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
		case IDM_FILE_NEWTEXT:
		{
			TCHAR szHelloTitle[] = L"Doc 1"; // cần thay đổi
			MDICREATESTRUCT mdiCreate;
			mdiCreate.szClass = L"MDI_TEXTWINDOW_CHILD";
			mdiCreate.szTitle = szHelloTitle;
			mdiCreate.style = WS_CHILD | WS_VISIBLE | WS_VSCROLL | WM_HSCROLL;
			mdiCreate.hOwner = hInst;
			mdiCreate.x = CW_USEDEFAULT;
			mdiCreate.y = CW_USEDEFAULT;
			mdiCreate.cx = CW_USEDEFAULT;
			mdiCreate.cy = CW_USEDEFAULT;
			//mdiCreate.
			mdiCreate.style = 0;
			// Tham số “mở”, chuyển đến WM_CREATE
			mdiCreate.lParam = NULL;
			SendMessage(hWndMDIClient, WM_MDICREATE, 0, (LONG)
				(LPMDICREATESTRUCT)&mdiCreate);
			return DefFrameProc(hWnd, hWndMDIClient, message, wParam, lParam);
		}
		break;
		case ID_FILE_NEWBITMAP:
		{
			TCHAR szHelloTitle[] = L"Doc 1"; // cần thay đổi
			MDICREATESTRUCT mdiCreate;
			mdiCreate.szClass = L"MDI_DRAWWINDOW_CHILD";
			mdiCreate.szTitle = szHelloTitle;
			mdiCreate.style = WS_CHILD | WS_VISIBLE | WS_VSCROLL | WM_HSCROLL;
			mdiCreate.hOwner = hInst;
			mdiCreate.x = CW_USEDEFAULT;
			mdiCreate.y = CW_USEDEFAULT;
			mdiCreate.cx = CW_USEDEFAULT;
			mdiCreate.cy = CW_USEDEFAULT;
			//mdiCreate.
			mdiCreate.style = 0;
			// Tham số “mở”, chuyển đến WM_CREATE
			mdiCreate.lParam = NULL;
			SendMessage(hWndMDIClient, WM_MDICREATE, 0, (LONG)
				(LPMDICREATESTRUCT)&mdiCreate);
			return DefFrameProc(hWnd, hWndMDIClient, message, wParam, lParam);
		//	MDICREATESTRUCT mcs;
		//	HWND hChild;

		//	mcs.szTitle = L"[Untitled]";
		//	mcs.szClass = L"MDI_DRAWWINDOW_CHILD";
		//	mcs.hOwner = hInst;
		//	mcs.x = mcs.cx = CW_USEDEFAULT;
		//	mcs.y = mcs.cy = CW_USEDEFAULT;
		////	mcs.style = MDIS_ALLCHILDSTYLES;

		//	hChild = (HWND)SendMessage(hWndMDIClient, WM_MDICREATE, 0, (LONG)&mcs);
		//	if (!hChild)
		//	{
		//		MessageBox(hWndMDIClient, L"MDI Child creation failed.", L"Oh Oh...",
		//			MB_ICONEXCLAMATION | MB_OK);
		//	}
			//return DefFrameProc(hWnd, hWndMDIClient, message, wParam, lParam);
		}
		break;
		
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
		break;
	case WM_CREATE:
	{
		
		//
		CLIENTCREATESTRUCT ccs;
		ccs.hWindowMenu = GetSubMenu(GetMenu(hWnd), WINDOW_MENU_POS);
		ccs.idFirstChild = 1;
		
		hWndMDIClient = CreateWindow(L"MDICLIENT",
			NULL,
			WS_CHILD | WS_CLIPCHILDREN | WS_VSCROLL |
			WS_HSCROLL,
			0, 0, 0, 0,
			hWnd,
			(HMENU)NULL,
			hInst, (LPSTR)&ccs);
	
		ShowWindow(hWndMDIClient, SW_SHOW);
		
		//HWND u = CreateWindow(L"MDI_DRAWWINDOW_CHILD", L"HELLO", WS_CHILD | WS_CLIPCHILDREN | WS_VSCROLL, 0, 0, 100, 100, hWnd, 0, hInst, 0);
		//ShowWindow(u, 1);
		return DefFrameProc(hWnd, hWndMDIClient, message, wParam, lParam);

	}
	case WM_SETFOCUS:
	{
		HMENU mymenu = GetMenu(hWnd);
		EnableMenuItem(mymenu, ID_EDIT_CUT, MF_BYCOMMAND | MF_GRAYED);
		EnableMenuItem(mymenu, ID_EDIT_COPY, MF_BYCOMMAND | MF_GRAYED);
		EnableMenuItem(mymenu, ID_EDIT_PASTE, MF_BYCOMMAND | MF_GRAYED);
		EnableMenuItem(mymenu, ID_EDIT_SELECTALL, MF_BYCOMMAND | MF_GRAYED);
		EnableMenuItem(mymenu, ID_FORMAT_CHOOSEFONT, MF_BYCOMMAND | MF_GRAYED);
		EnableMenuItem(mymenu, ID_EDIT_CUT, MF_BYCOMMAND | MF_GRAYED);
		EnableMenuItem(mymenu, ID_DRAW_PIXEL, MF_BYCOMMAND | MF_GRAYED);
		EnableMenuItem(mymenu, ID_DRAW_RECTANGLE, MF_BYCOMMAND | MF_GRAYED);
		EnableMenuItem(mymenu, ID_DRAW_ELLIPSE, MF_BYCOMMAND | MF_GRAYED);
		EnableMenuItem(mymenu, ID_DRAW_LINE, MF_BYCOMMAND | MF_GRAYED);
	}
	return DefFrameProc(hWnd, hWndMDIClient, message, wParam, lParam);

	case WM_SIZE:
	{
		UINT w, h;
		w = LOWORD(lParam);
		h = HIWORD(lParam);
		MoveWindow(hWndMDIClient, 0, 0, w, h, true);
	}
	return DefFrameProc(hWnd, hWndMDIClient, message, wParam, lParam);

	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		// TODO: Add any drawing code here...
		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

LRESULT CALLBACK WndProcDraw(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	PAINTSTRUCT ps;
	HDC hdc;

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
	case WM_CREATE:
	{
		
		//
		return DefMDIChildProc(hWnd, message, wParam, lParam);
		//break;


	}
	break;
	case WM_SETFOCUS:
	{
		HMENU mymenu = GetMenu(hWndFrame);
		EnableMenuItem(mymenu, ID_EDIT_CUT, MF_BYCOMMAND | MF_GRAYED);
		EnableMenuItem(mymenu, ID_EDIT_COPY, MF_BYCOMMAND | MF_GRAYED);
		EnableMenuItem(mymenu, ID_EDIT_PASTE, MF_BYCOMMAND | MF_GRAYED);
		EnableMenuItem(mymenu, ID_EDIT_SELECTALL, MF_BYCOMMAND | MF_GRAYED);
		EnableMenuItem(mymenu, ID_FORMAT_CHOOSEFONT, MF_BYCOMMAND | MF_GRAYED);
		EnableMenuItem(mymenu, ID_EDIT_CUT, MF_BYCOMMAND | MF_GRAYED);
		EnableMenuItem(mymenu, ID_DRAW_PIXEL, MF_BYCOMMAND | MF_ENABLED);
		EnableMenuItem(mymenu, ID_DRAW_RECTANGLE, MF_BYCOMMAND | MF_ENABLED);
		EnableMenuItem(mymenu, ID_DRAW_ELLIPSE, MF_BYCOMMAND | MF_ENABLED);
		EnableMenuItem(mymenu, ID_DRAW_LINE, MF_BYCOMMAND | MF_ENABLED);
	}
	return DefMDIChildProc(hWnd, message, wParam, lParam);
	
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		// TODO: Add any drawing code here...
		EndPaint(hWnd, &ps);
		break;
	case WM_SIZE:
	{

	}
	return DefMDIChildProc(hWnd, message, wParam, lParam);

	case WM_DESTROY:
		//PostQuitMessage(0);
		return DefMDIChildProc(hWnd, message, wParam, lParam);
		break;
	default:
		return DefMDIChildProc(hWnd, message, wParam, lParam);
		//return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}


LRESULT CALLBACK WndProcText(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	PAINTSTRUCT ps;
	HDC hdc;
	static HWND texthWnd;
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
	case WM_CREATE:
	{
		RECT rect;
		GetClientRect(hWnd, &rect);
		texthWnd = CreateWindow(L"EDIT", NULL, WS_CHILD | WS_VISIBLE | WS_VSCROLL,
			0, 0, (rect.right - rect.left), (rect.bottom - rect.top), hWnd, NULL, hInst, NULL);
		
		//
		return DefMDIChildProc(hWnd, message, wParam, lParam);
		break;


	}
	break;
	case WM_SETFOCUS:
	{
		HMENU mymenu = GetMenu(hWndFrame);
		EnableMenuItem(mymenu, ID_EDIT_CUT, MF_BYCOMMAND | MF_ENABLED);
		EnableMenuItem(mymenu, ID_EDIT_COPY, MF_BYCOMMAND | MF_ENABLED);
		EnableMenuItem(mymenu, ID_EDIT_PASTE, MF_BYCOMMAND | MF_ENABLED);
		EnableMenuItem(mymenu, ID_EDIT_SELECTALL, MF_BYCOMMAND | MF_ENABLED);
		EnableMenuItem(mymenu, ID_FORMAT_CHOOSEFONT, MF_BYCOMMAND | MF_GRAYED);
		EnableMenuItem(mymenu, ID_DRAW_PIXEL, MF_BYCOMMAND | MF_GRAYED);
		EnableMenuItem(mymenu, ID_DRAW_RECTANGLE, MF_BYCOMMAND | MF_GRAYED);
		EnableMenuItem(mymenu, ID_DRAW_ELLIPSE, MF_BYCOMMAND | MF_GRAYED);
		EnableMenuItem(mymenu, ID_DRAW_LINE, MF_BYCOMMAND | MF_GRAYED);
	}
	return DefMDIChildProc(hWnd, message, wParam, lParam);

	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		// TODO: Add any drawing code here...
		EndPaint(hWnd, &ps);
		break;
	case WM_SIZE:
	{

	}
	return DefMDIChildProc(hWnd, message, wParam, lParam);

	case WM_DESTROY:
		//PostQuitMessage(0);
		return DefMDIChildProc(hWnd, message, wParam, lParam);
		break;
	default:
		return DefMDIChildProc(hWnd, message, wParam, lParam);
		//return DefWindowProc(hWnd, message, wParam, lParam);
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
