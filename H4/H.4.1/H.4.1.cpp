// H.4.1.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "H.4.1.h"

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
//

INT_PTR CALLBACK DrawDialog(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);
void paintFigure(HWND hWnd, int iColor, int iFigure);

int currentColor = IDC_RADIO_BLACK;
int currentFigure = IDC_RADIO_RECTANGLE;

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
	LoadString(hInstance, IDC_H41, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// Perform application initialization:
	if (!InitInstance (hInstance, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_H41));

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
	wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_H41));
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= MAKEINTRESOURCE(IDC_H41);
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

	
	switch (message)
	{
	case WM_COMMAND:
		wmId    = LOWORD(wParam);
		wmEvent = HIWORD(wParam);
		// Parse the menu selections:
		switch (wmId)
		{
		case IDM_DRAW:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOG_DRAW), hWnd, DrawDialog);
			break;
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

INT_PTR CALLBACK DrawDialog(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	HDC hdc;
	UNREFERENCED_PARAMETER(lParam);
	static int iColor = currentColor;
	static int iFigure = currentFigure;
	static HWND hCtrlFigure;
	static bool isInit = true;
	switch (message)
	{
	case WM_INITDIALOG:
	{
		hCtrlFigure = GetDlgItem(hDlg, IDC_FIGUREBOX);
		CheckRadioButton(hDlg, IDC_RADIO_BLACK, IDC_RADIO_WHITE, iColor);
		CheckRadioButton(hDlg, IDC_RADIO_RECTANGLE, IDC_RADIO_ELLIPSE, iFigure);
		iColor = currentColor;
		iFigure = currentFigure; 
		isInit = true;
		InvalidateRect(hDlg, 0, TRUE);
		UpdateWindow(hDlg);
		//InvalidateRect(hCtrlFigure, 0, TRUE);
		//paintFigure(hCtrlFigure, IDC_RADIO_BLACK, IDC_RADIO_RECTANGLE);
		//SetFocus(GetDlgItem(hDlg, iColor));
		//SetFocus(GetDlgItem(hDlg, iFigure));
		

	}
		return (INT_PTR)TRUE;
	case WM_PAINT:
	{
		if (isInit)
		{
			paintFigure(hCtrlFigure, iColor, iFigure);
			isInit = false;
		}
		//paintFigure(hCtrlFigure, iColor, iFigure);
	}
	return (INT_PTR)TRUE;
	case WM_COMMAND:
	{
		switch (LOWORD(wParam))
		{
		case IDOK:
		{
			currentColor = iColor;
			currentFigure = iFigure;
			
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
		case IDCANCEL:
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
		case IDC_RADIO_BLACK:
		case IDC_RADIO_BLUE:
		case IDC_RADIO_GREEN:
		case IDC_RADIO_CYAN:
		case IDC_RADIO_RED:
		case IDC_RADIO_MAGENTA:
		case IDC_RADIO_WHITE:
		case IDC_RADIO_YELLOW:
		{

			iColor = LOWORD(wParam);
			
			SetFocus(GetDlgItem(hDlg, iColor));
			CheckRadioButton(hDlg, IDC_RADIO_BLACK, IDC_RADIO_WHITE, iColor);
			CheckRadioButton(hDlg, IDC_RADIO_RECTANGLE, IDC_RADIO_ELLIPSE, iFigure);
			///InvalidateRect(hDlg, 0, TRUE);
			//UpdateWindow(hDlg);
			paintFigure(hCtrlFigure, iColor, iFigure);
			return (INT_PTR)TRUE;
		}
		break;
		case IDC_RADIO_RECTANGLE:
		case IDC_RADIO_ELLIPSE:
		{
			iFigure = LOWORD(wParam);
			//SetFocus(GetDlgItem(hDlg, iColor));
			SetFocus(GetDlgItem(hDlg, iFigure));
			CheckRadioButton(hDlg, IDC_RADIO_BLACK, IDC_RADIO_WHITE, iColor);
			CheckRadioButton(hDlg, IDC_RADIO_RECTANGLE, IDC_RADIO_ELLIPSE, iFigure);
			//InvalidateRect(hCtrlFigure, 0, TRUE);
			//UpdateWindow(hCtrlFigure);
			paintFigure(hCtrlFigure, iColor, iFigure);
			return (INT_PTR)TRUE;
		}
		break;
		}
	}
		/*if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;*/
	}
	return (INT_PTR)FALSE;
}

COLORREF chooseColor(int c)
{
	COLORREF mcolor;
	switch (c)
	{
	case IDC_RADIO_BLACK:
		mcolor = RGB(0, 0, 0);
		break;
	case IDC_RADIO_BLUE:
		mcolor = RGB(0, 0, 255);
		break;
	case IDC_RADIO_GREEN:
		mcolor = RGB(0, 255, 0);
		break;
	case IDC_RADIO_MAGENTA:
		mcolor = RGB(255, 0, 255);
		break;
	case IDC_RADIO_WHITE:
		mcolor = RGB(255, 255, 255);
		break;
	case IDC_RADIO_CYAN:
		mcolor = RGB(0, 255, 255);
		break;
	case IDC_RADIO_RED:
		mcolor = RGB(255, 0, 0);
		break;
	case IDC_RADIO_YELLOW:
		mcolor = RGB(255, 255, 0);
		break;
	}
	return mcolor;
}
void paintFigure(HWND hWnd, int iColor, int iFigure)
{
	COLORREF mcolor = chooseColor(iColor);

	HDC hdc = GetDC(hWnd);
	
	SelectObject(hdc, GetStockObject(DC_BRUSH));
	SetDCBrushColor(hdc, mcolor);
	RECT client;
	GetClientRect(hWnd, &client);
	//SetROP2(hdc, R2_NOTXORPEN);
	InvalidateRect(hWnd, 0, TRUE);
	UpdateWindow(hWnd);
	switch (iFigure)
	{
	case IDC_RADIO_RECTANGLE:
		Rectangle(hdc, client.left, client.top, client.right, client.bottom);
		break;
	case IDC_RADIO_ELLIPSE:
		Ellipse(hdc, client.left, client.top, client.right, client.bottom);
		break;
	default:
		break;
	}
	ReleaseDC(hWnd, hdc);
	
}