// H9.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "H9.h"

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

bool TaskbarDeleteIcon(HWND hWnd, UINT uID);
bool TaskbarAddIcon(HWND hWnd, UINT uID, HICON hIcon, LPCWSTR lpszTip);
void doMinimize(HWND hWnd);
void setHook(HWND hWnd);
void unHook(HWND hWnd);
INT_PTR CALLBACK LockDLG(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);
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
	LoadString(hInstance, IDC_H9, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// Perform application initialization:
	if (!InitInstance (hInstance, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_H9));

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
	wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_H9));
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= MAKEINTRESOURCE(IDC_H9);
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

   //ShowWindow(hWnd, nCmdShow);
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
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
		break;
	case WM_CREATE:
	{
		DialogBox(hInst, MAKEINTRESOURCE(IDD_LOCK), hWnd, LockDLG);
		break;
	}
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


INT_PTR CALLBACK LockDLG(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
	{
		setHook(hDlg);
	}
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
			case IDOK: case IDCANCEL: case IDC_BUTTON_QUIT:
			{
				unHook(hDlg);
				EndDialog(hDlg, LOWORD(wParam));
				PostQuitMessage(0);
				return (INT_PTR)TRUE;
			}

			case IDC_BUTTON_SYSTEMTRAY:
			{
				doMinimize(hDlg);
				return (INT_PTR)TRUE;
			}
		}
		break;

	case MY_WM_NOTIFYICON:
	{
		if (lParam == WM_LBUTTONDOWN)
		{
			TaskbarDeleteIcon(hDlg, TRAY_ICON_ID);
			ShowWindow(hDlg, SW_SHOW);
			ShowWindow(hDlg, SW_RESTORE);
		}
		return (INT_PTR)TRUE;
	}
	}
	return (INT_PTR)FALSE;
}

void setHook(HWND hWnd)
{
	HINSTANCE hinst;
	hinst = LoadLibrary(L"LOCK_KEYBOARD");
	if (hinst != NULL)
	{
		typedef void(*setHook)();
		setHook f;
		f = (setHook)GetProcAddress(hinst, "setHook");
		if (f != NULL)
		{
			f();
			//MessageBox(0, L"Sethook", L"", MB_OK);
		}
	}
}

void unHook(HWND hWnd)
{
	HINSTANCE hinst;
	hinst = LoadLibrary(L"LOCK_KEYBOARD");
	if (hinst != NULL)
	{
		typedef void(*unHook)();
		unHook f;
		f = (unHook)GetProcAddress(hinst, "unHook");
		if (f != NULL)
		{
			f();
			//MessageBox(0, L"Unhook", L"", MB_OK);
		}
	}
}
void doMinimize(HWND hWnd)
{
	ShowWindow(hWnd, SW_HIDE);
	HICON hIcon = LoadIcon(hInst, MAKEINTRESOURCE(IDI_H9));
	TaskbarAddIcon(hWnd, TRAY_ICON_ID, hIcon, L"Xin chao");
	
}

bool TaskbarAddIcon(HWND hWnd, UINT uID, HICON hIcon, LPCWSTR lpszTip)
{
	BOOL res;
	NOTIFYICONDATA tnid;
	tnid.cbSize = sizeof(NOTIFYICONDATA);
	tnid.hWnd = hWnd;
	tnid.uID = uID;
	tnid.uFlags = NIF_MESSAGE | NIF_ICON | NIF_TIP;
	tnid.uCallbackMessage = MY_WM_NOTIFYICON;
	tnid.hIcon = hIcon;
	if (lpszTip)
		lstrcpyn(tnid.szTip, lpszTip, sizeof(tnid.szTip));
	else
		tnid.szTip[0] = '\0';
	res = Shell_NotifyIcon(NIM_ADD, &tnid);
	if (hIcon)
		DestroyIcon(hIcon);
	
	return res;
}

bool TaskbarDeleteIcon(HWND hWnd, UINT uID)
{
	bool res;

	NOTIFYICONDATA tnid;
	tnid.cbSize = sizeof(NOTIFYICONDATA);
	tnid.hWnd = hWnd;
	tnid.uID = uID;

	res = Shell_NotifyIcon(NIM_DELETE, &tnid);
	return res;
}