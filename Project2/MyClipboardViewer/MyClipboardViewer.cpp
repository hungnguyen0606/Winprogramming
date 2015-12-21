// MyClipboardViewer.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "MyClipboardViewer.h"

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


struct ClipData
{
	char* ansi;
	TCHAR* unicode;
	HBITMAP bitmap;

	ClipData()
	{
		ansi = NULL;
		unicode = NULL;
		bitmap = NULL;
	}

	void setAnsi(char* str)
	{
		if (ansi != NULL)
			delete[] ansi;
		ansi = new char[strlen(str) + 1];
		strcpy(ansi, str);
	}

	void setUnicode(TCHAR* str)
	{
		if (unicode != NULL)
			delete[] unicode;
		unicode = new TCHAR[lstrlen(str) + 1];
		lstrcpy(unicode, str);
	}

	void setBitmap(HBITMAP bm)
	{
		if (bitmap != NULL)
			DeleteObject(bitmap);
		bitmap = (HBITMAP)CopyImage(bm, IMAGE_BITMAP, 0, 0, LR_DEFAULTSIZE);
	}
};
//-------------------------------------------------------------------

int onCreate(HWND hWnd, HWND& hWndNextViewer);
int onDestroy(HWND hWnd, HWND hWndNextViewer);
int onDrawClipboard(HWND hWnd, HWND hWndNextViewer, ClipData& dat);
int onChangeSize(HWND hWnd, HWND hAnsi, HWND hUnicode, HWND hBitmap);
int onDrawClipboard(HWND hWnd, HWND hWndNextViewer);
int onChangeClipboardChain(HWND hWndRemove, HWND hWndAfter, HWND& hWndNextViewer);
int updateClipboardData(HWND hWnd, ClipData& dat);

int onPaint(HWND hWnd, HDC& hdc, const ClipData& dat);
//-------------------------------------------------------------------


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
	LoadString(hInstance, IDC_MYCLIPBOARDVIEWER, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// Perform application initialization:
	if (!InitInstance (hInstance, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_MYCLIPBOARDVIEWER));

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
	wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_MYCLIPBOARDVIEWER));
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= MAKEINTRESOURCE(IDC_MYCLIPBOARDVIEWER);
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
	static HWND hAnsi = NULL;
	static HWND hUnicode = NULL;
	static HWND hBitmap = NULL;
	static HWND hWndNextViewer;
	static ClipData dat;

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
		onCreate(hWnd, hWndNextViewer);
		RECT rect;
		GetWindowRect(hWnd, &rect);
		int wid = (rect.right - rect.left) / 3;
		int hei = (rect.bottom - rect.top);
		//hAnsi = CreateWindow(L"STATIC", L"Ansi", WS_CHILD | WS_VISIBLE | WS_VSCROLL, 0, 0, wid, hei , hWnd, 0, hInst, 0);
		//hUnicode = CreateWindow(L"EDIT", L"Unicode", WS_CHILD | WS_VISIBLE | WS_VSCROLL, 0, 0, wid, hei, hWnd, 0, hInst, 0);
		//hBitmap = CreateWindow(L"STATIC", L"Bitmap", WS_CHILD | WS_VISIBLE | WS_VSCROLL, 0, 0, wid, hei, hWnd, 0, hInst, 0);
		onChangeSize(hWnd, hAnsi, hUnicode, hBitmap);
		break;
	}
	case WM_SIZE:
	{
		onChangeSize(hWnd, hAnsi, hUnicode, hBitmap);
		break;
	}
	case WM_CHANGECBCHAIN:
	{
		onChangeClipboardChain((HWND)wParam, (HWND)lParam, hWndNextViewer);
		break;
	}
	case WM_DRAWCLIPBOARD:
	{
		
		onDrawClipboard(hWnd, hWndNextViewer, dat);
		break;
	}
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		// TODO: Add any drawing code here...
		RECT r;
		GetClientRect(hWnd, &r);
		//DrawText(hdc, L"ajf", 3, &r, DT_LEFT);
		onPaint(hWnd, hdc, dat);
		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY:
		onDestroy(hWnd, hWndNextViewer);
		//PostQuitMessage(0);
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

int onDestroy(HWND hWnd, HWND hWndNextViewer)
{
	ChangeClipboardChain(hWnd, hWndNextViewer);
	PostQuitMessage(0);
	return 0;
}

int onCreate(HWND hWnd, HWND& hWndNextViewer)
{
	hWndNextViewer = SetClipboardViewer(hWnd);
	return 0;
}

int onDrawClipboard(HWND hWnd, HWND hWndNextViewer, ClipData& dat)
{
	
	if (hWndNextViewer != NULL)
		SendMessage(hWndNextViewer, WM_DRAWCLIPBOARD, 0, 0);
	updateClipboardData(hWnd, dat);
	InvalidateRect(hWnd, 0, TRUE);
	UpdateWindow(hWnd);
	return 0;
}

int onPaint(HWND hWnd,  HDC& hdc, const ClipData& dat)
{
	
	
	RECT rect, title, rAnsi, rUnicode, rBitmap;
	
	GetClientRect(hWnd, &rect);
	int wid = rect.right - rect.left;

	//Draw title
	title = rect;
	title.right = wid / 3;
	title.bottom = title.top + 50;
	TCHAR tit[][20] = { L"Ansi", L"Unicode", L"Bitmap" };
	for (int i = 0; i < 3; ++i)
	{
		DrawText(hdc, tit[i], lstrlen(tit[i]), &title, DT_CENTER);
		title.left += wid / 3;
		title.right += wid / 3;
	}
	//draw boundary
	MoveToEx(hdc, rect.left, title.bottom - 10, 0);
	LineTo(hdc, rect.right, title.bottom - 10);

	MoveToEx(hdc, wid / 3, rect.top, 0);
	LineTo(hdc, wid / 3, rect.bottom);
	
	MoveToEx(hdc, wid * 2 / 3, rect.top, 0);
	LineTo(hdc, wid * 2 / 3, rect.bottom);
	//
	rect.top += 50; //space for title
	rAnsi = rUnicode = rBitmap = rect;
	
	//rectangle for bitmap
	rBitmap.left = wid * 2 / 3 + 5;
	rBitmap.right = rect.right - 5;
	//rectangle for unicode
	rUnicode.left = wid / 3 + 5;
	rUnicode.right = wid * 2 / 3 - 5;
	
	//rectangle for Ansi
	rAnsi.right = wid / 3 - 5;
	
	if (dat.ansi != NULL)
	{
		TCHAR *tmp = new TCHAR[strlen(dat.ansi) + 1];
		for (int i = 0; i <= strlen(dat.ansi); ++i)
		{
			tmp[i] = TCHAR(dat.ansi[i]);
		}
		if (tmp != NULL)
		{
			DrawText(hdc, tmp, lstrlen(tmp), &rAnsi, DT_LEFT | DT_WORDBREAK);
			delete[]tmp;
		}
				}
	if (dat.unicode != NULL)
	{
		DrawText(hdc, dat.unicode, lstrlen(dat.unicode), &rUnicode, DT_LEFT | DT_WORDBREAK);
		
	}

	if (dat.bitmap != NULL)
	{
		
		HDC memDc = CreateCompatibleDC(hdc);
		BITMAP img;
		GetObject(dat.bitmap, sizeof(BITMAP), &img);
		HBITMAP tmpBitmap = (HBITMAP)SelectObject(memDc, dat.bitmap);

		
		StretchBlt(hdc, rBitmap.left, rBitmap.top, rBitmap.right - rBitmap.left, rBitmap.bottom - rBitmap.top, memDc, 0, 0, img.bmWidth, img.bmHeight, SRCCOPY);
		SelectObject(memDc, tmpBitmap);

		DeleteDC(memDc);
		
	}
	
	return 0;
}

int onChangeClipboardChain(HWND hWndRemove, HWND hWndAfter, HWND& hWndNextViewer)
{
	if (hWndRemove == hWndNextViewer)
		hWndNextViewer = hWndAfter;
	else
		if (hWndNextViewer != NULL)
			SendMessage(hWndNextViewer, WM_CHANGECBCHAIN, (WPARAM)hWndRemove, (LPARAM)hWndAfter);

	return 0;
}

int onChangeSize(HWND hWnd, HWND hAnsi, HWND hUnicode, HWND hBitmap)
{
	if (hWnd == NULL)
		return -1;

	RECT rect;
	GetClientRect(hWnd, &rect);
	int wid = rect.right - rect.left;
	int hei = rect.bottom - rect.top;

	if (hAnsi != NULL)
	{
		MoveWindow(hAnsi, 0, 0, wid / 3, hei, TRUE);
	}
	if (hUnicode != NULL)
	{
		MoveWindow(hUnicode, wid/3, 0, wid / 3, hei, TRUE);
	}
	if (hBitmap != NULL)
	{
		MoveWindow(hBitmap, wid*2/3, 0, wid / 3, hei, TRUE);
	}
	
	return 0;
}

int updateClipboardData(HWND hWnd, ClipData& dat)
{
	if (OpenClipboard(hWnd))
	{
		if (IsClipboardFormatAvailable(CF_TEXT))
		{
			HANDLE hData = GetClipboardData(CF_TEXT);
			if (hData != NULL)
			{
				char* ansi = (char*)GlobalLock(hData);
				dat.setAnsi(ansi);
				GlobalUnlock(hData); 
			}
		}
		if (IsClipboardFormatAvailable(CF_UNICODETEXT))
		{
			HANDLE hData = GetClipboardData(CF_UNICODETEXT);
			if (hData != NULL)
			{
				TCHAR* unicode = (TCHAR*)GlobalLock(hData);
				dat.setUnicode(unicode);
				GlobalUnlock(hData);
			}
		}
		if (IsClipboardFormatAvailable(CF_BITMAP))
		{
			HANDLE hData = GetClipboardData(CF_BITMAP);
			if (hData != NULL)
			{
				dat.setBitmap((HBITMAP)hData);
			}
		}

		CloseClipboard();
	}
	
	return 0;
}