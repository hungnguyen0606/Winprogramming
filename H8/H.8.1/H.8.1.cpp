// H.8.1.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "H.8.1.h"

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
INT_PTR CALLBACK ToolDlg(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);

extern  int __cdecl Cong(int, int);
extern  int __cdecl Tru(int, int);
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
	LoadString(hInstance, IDC_H81, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// Perform application initialization:
	if (!InitInstance (hInstance, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_H81));

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
	wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_H81));
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= 0;// MAKEINTRESOURCE(IDC_H81);
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

   hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPED,
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
		wmId = LOWORD(wParam);
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
	
		DialogBox(hInst, MAKEINTRESOURCE(IDD_TOOLDLG), hWnd, ToolDlg);
		
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

INT_PTR CALLBACK ToolDlg(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	TCHAR s[111];
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
	{
		SetDlgItemText(hDlg, IDC_VALUE_A, L"0");
		SetDlgItemText(hDlg, IDC_VALUE_B, L"0");
		SetDlgItemText(hDlg, IDC_RESULT, L"");

		
		return (INT_PTR)TRUE;
	}
		

	case WM_COMMAND:
		/*if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			PostQuitMessage(0);
			return (INT_PTR)TRUE;
		}
		break;*/
		switch (LOWORD(wParam))
		{
		case IDC_ADD:
		{
			BOOL sucA, sucB;
			int a = (int)GetDlgItemInt(hDlg, IDC_VALUE_A, &sucA, TRUE);
			int b = (int)GetDlgItemInt(hDlg, IDC_VALUE_B, &sucB, TRUE);
				
			_stprintf_p(s, 111, L"Ket qua %d + %d = %d", a, b, Cong(a,b));
			SetDlgItemText(hDlg, IDC_RESULT, (LPCWSTR)s);
		
			break;
		}
		case IDC_SUB:
		{
			BOOL sucA, sucB;
			int a = (int)GetDlgItemInt(hDlg, IDC_VALUE_A, &sucA, TRUE);
			int b = (int)GetDlgItemInt(hDlg, IDC_VALUE_B, &sucB, TRUE);

			_stprintf_p(s, 111, L"Ket qua %d - %d = %d", a, b, Tru(a, b));
			SetDlgItemText(hDlg, IDC_RESULT, (LPCWSTR)s);
			
			break;
		}

		case IDC_MUL:
		{
			BOOL sucA, sucB;
			int a = (int)GetDlgItemInt(hDlg, IDC_VALUE_A, &sucA, TRUE);
			int b = (int)GetDlgItemInt(hDlg, IDC_VALUE_B, &sucB, TRUE);

			typedef int(*Nhan)(int, int);
			HINSTANCE hinstLib;
			Nhan func;
			hinstLib = LoadLibrary(L"DLL_Lib");

			if (hinstLib == NULL)
			{
				MessageBox(hDlg, L"Cannot load DLL", L"Error", MB_OK);
				break;
			}
			func = (Nhan)GetProcAddress(hinstLib, "Nhan");
			if (func == NULL)
			{
				MessageBox(hDlg, L"Cannot load function", L"Error", MB_OK);
				break;
			}
			_stprintf_p(s, 111, L"Ket qua %d * %d = %d", a, b, func(a, b));
			SetDlgItemText(hDlg, IDC_RESULT, s);
			break;
		}
		case IDC_DIV:
		{
			BOOL sucA, sucB;
			int a = (int)GetDlgItemInt(hDlg, IDC_VALUE_A, &sucA, TRUE);
			int b = (int)GetDlgItemInt(hDlg, IDC_VALUE_B, &sucB, TRUE);

			typedef int(*Chia)(int, int);
			HINSTANCE hinstLib;
			Chia func;
			hinstLib = LoadLibrary(L"DLL_Lib");

			if (hinstLib == NULL)
			{
				MessageBox(hDlg, L"Cannot load DLL", L"Error", MB_OK);
				break;
			}
			func = (Chia)GetProcAddress(hinstLib, "Chia");
			if (func == NULL)
			{
				MessageBox(hDlg, L"Cannot load function", L"Error", MB_OK);
				break;
			}
			if (b == 0)
				_stprintf_s(s, 111, L"Division by zero!!!");
			else
				_stprintf_p(s, 111, L"Ket qua %d / %d = %d", a, b, func(a, b));
			SetDlgItemText(hDlg, IDC_RESULT, s);
			break;

		}
		case IDC_QUIT:
		{
			EndDialog(hDlg, LOWORD(wParam));
			PostQuitMessage(0);
			break;
		}
		default:
			break;
		}
	}
	return (INT_PTR)FALSE;
}
