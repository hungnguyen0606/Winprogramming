// H.10.1.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "H.10.1.h"

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

void LoadFileBitmap(HWND hWnd, HBITMAP& img);
void FitToWindow(HWND hWnd, HBITMAP& img);
void getCurrentWindowPos(HWND hWnd, HBITMAP& img, int &x, int &y);
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
	LoadString(hInstance, IDC_H101, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// Perform application initialization:
	if (!InitInstance (hInstance, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_H101));

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
	wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_H101));
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= MAKEINTRESOURCE(IDC_H101);
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

   hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW | WS_VSCROLL | WS_HSCROLL,
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
	static HBITMAP img = NULL;
	

	switch (message)
	{
	case WM_CREATE:
	{
		HMENU menu;
		menu = GetMenu(hWnd);
		EnableMenuItem(menu, ID_FITTOWINDOW, MF_BYCOMMAND | MF_GRAYED);
		//EnableMenuItem(menu, IDM_ABOUT, MF_BYCOMMAND | MF_GRAYED);
		//ShowScrollBar(hWnd, SB_BOTH, TRUE);
		//EnableScrollBar(hWnd, SB_BOTH, ESB_ENABLE_BOTH);
		
		break;
	}
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
		case ID_LOADRCBITMAP:
		{
			
			if (img != NULL)
				DeleteObject(img);
			HMENU menu;
			menu = GetMenu(hWnd);
			EnableMenuItem(menu, ID_FITTOWINDOW, MF_BYCOMMAND | MF_ENABLED);

			img = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BITMAP_MARU));
			InvalidateRect(hWnd, 0, TRUE);
			UpdateWindow(hWnd);
			break;
		}
		case ID_LOADFILEBITMAP:
		{
			HMENU menu;
			menu = GetMenu(hWnd);
			EnableMenuItem(menu, ID_FITTOWINDOW, MF_BYCOMMAND | MF_ENABLED);
			LoadFileBitmap(hWnd, img);
		
			break;
		}
		case ID_FITTOWINDOW:
		{
			FitToWindow(hWnd, img);
			break;
		}
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
		break;
	case WM_VSCROLL: case WM_HSCROLL:
	{
		int who;
		if (message == WM_VSCROLL)
			who = SB_VERT;
		else
			who = SB_HORZ;
		SCROLLINFO st;
		st.cbSize = sizeof(SCROLLINFO);
		st.fMask = SIF_POS | SIF_RANGE | SIF_TRACKPOS;
		GetScrollInfo(hWnd, who, &st);
		SetScrollPos(hWnd, who, st.nTrackPos, TRUE);
		
		InvalidateRect(hWnd, 0, TRUE);
		UpdateWindow(hWnd);
		break;
	}
	case WM_PAINT:
	{
		if (img == NULL)
			break;
		hdc = BeginPaint(hWnd, &ps);
		// TODO: Add any drawing code here...
		HDC memDC = CreateCompatibleDC(hdc);
		HBITMAP hOldbmp = (HBITMAP)SelectObject(memDC, img);
		BITMAP bm;
		GetObject(img, sizeof(BITMAP), &bm);
		
		int stx, sty;
		getCurrentWindowPos(hWnd, img, stx, sty);
		BitBlt(hdc, 0, 0, bm.bmWidth, bm.bmHeight, memDC, stx, sty, SRCCOPY);
		SelectObject(memDC, hOldbmp);
		
		DeleteDC(memDC);
		EndPaint(hWnd, &ps);
		break;
	}
		
	case WM_DESTROY:

		DeleteObject(img);
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

void LoadFileBitmap(HWND hWnd, HBITMAP& img)
{
	if (img != NULL)
		DeleteObject(img);
	OPENFILENAME ofn; // CTDL dùng cho dialog open
	TCHAR szFile[5000];
	TCHAR szFilter[] = L"BMP file\0*.bmp\0Icon file\0*.ico\0\0";
	szFile[0] = '\0';
	// Khởi tạo struct
	ZeroMemory(&ofn, sizeof(OPENFILENAME));
	ofn.lStructSize = sizeof(OPENFILENAME);
	ofn.hwndOwner = hWnd; // handle của window cha
	ofn.lpstrFilter = szFilter;
	ofn.nFilterIndex = 1;
	ofn.lpstrFile = szFile; // chuỗi tên file trả về
	ofn.nMaxFile = sizeof(szFile);
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;
	BOOL a;
	a = GetOpenFileName(&ofn);
	
	if (a) {
		HANDLE timg = LoadImage(hInst, szFile, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
		img = (HBITMAP)timg;
	}
	
	

	InvalidateRect(hWnd, 0, TRUE);
	UpdateWindow(hWnd);
}

void FitToWindow(HWND hWnd, HBITMAP& img)
{
	if (img == NULL)
		return;
	BITMAP bm;
	RECT rect;
	HDC hdc, memDC, tDC;
	
	hdc = GetDC(hWnd);
	GetClientRect(hWnd, &rect);
	memDC = CreateCompatibleDC(hdc);
	tDC = CreateCompatibleDC(hdc);
	ReleaseDC(hWnd, hdc);

	HBITMAP hOldbmp = (HBITMAP)SelectObject(memDC, img);
	HBITMAP hZoom = CreateCompatibleBitmap(memDC, rect.right - rect.left, rect.bottom - rect.top);
	HBITMAP hZoomOld = (HBITMAP)SelectObject(tDC, hZoom);
	GetObject(img, sizeof(BITMAP), &bm);
	
	StretchBlt(tDC, 0, 0, rect.right - rect.left, rect.bottom - rect.top, memDC, 0, 0, bm.bmWidth, bm.bmHeight, SRCCOPY);
	
	img = (HBITMAP)SelectObject(memDC, hOldbmp);
	hZoom = (HBITMAP)SelectObject(tDC, hZoomOld);
	DeleteObject(img);
	img = hZoom;
	
	DeleteDC(memDC);
	InvalidateRect(hWnd, 0, TRUE);
	UpdateWindow(hWnd);
	
}

void getCurrentWindowPos(HWND hWnd, HBITMAP& img, int &x, int &y)
{
	if (img == NULL)
	{
		x = y = 0;
		return;
	}
	BITMAP bm;
	GetObject(img, sizeof(BITMAP), &bm);

	SCROLLINFO vst, hst;
	vst.cbSize = sizeof(SCROLLINFO);
	hst.cbSize = vst.cbSize;
	vst.fMask = SIF_POS | SIF_RANGE;
	hst.fMask = SIF_POS | SIF_RANGE;
	
	GetScrollInfo(hWnd, SB_VERT, &vst);
	GetScrollInfo(hWnd, SB_HORZ, &hst);
	
	x = int(bm.bmWidth * 1.0 * (hst.nPos - hst.nMin) / (hst.nMax - hst.nMin));
	y = int(bm.bmHeight * 1.0 * (vst.nPos - vst.nMin) / (vst.nMax - vst.nMin));

}