// H.5.1.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "H.5.1.h"
#include "WindowManager.h"
#include "TextWindow.h"
#include "DrawWindow.h"
#include "Global.h"
#include "Shape.h"
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

//mydefine
#define WINDOW_MENU_POS 4
#define ID_FIRST_CHILD 1


ghInst hinst;
hWndFrame hwndFrame;
hWndMDIClient hwndMDIClient;
HWND hWndFrame::hwndframe = 0;
HWND hWndMDIClient::hwndMDIClient = 0;
HINSTANCE ghInst::hinst = 0;


LRESULT CALLBACK MDICloseProc(HWND hMDIWnd, LPARAM lParam);

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
	LoadString(hInstance, IDC_H51, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);
	myTextWindow::MyRegisterClass(hInstance);
	myDrawWindow::MyRegisterClass(hInstance);
	// Perform application initialization:
	if (!InitInstance (hInstance, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_H51));

	// Main message loop:
	while (GetMessage(&msg, NULL, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}
//	MDICREATESTRUCT ccs;
	
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
	wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_H51));
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_APPWORKSPACE + 1);
	wcex.lpszMenuName	= MAKEINTRESOURCE(IDC_H51);
	wcex.lpszClassName	= L"MDI_FRAME";
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
   hinst() = hInst;
   hWnd = CreateWindow(L"MDI_FRAME", szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, hInstance, NULL);

   hwndFrame() = hWnd;

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

void adjustEdit(UINT enable)
{
	HMENU mymenu = GetMenu(hwndFrame());
	EnableMenuItem(mymenu, ID_EDIT_CUT, MF_BYCOMMAND | enable);
	EnableMenuItem(mymenu, ID_EDIT_COPY, MF_BYCOMMAND | enable);
	EnableMenuItem(mymenu, ID_EDIT_PASTE, MF_BYCOMMAND | enable);
	EnableMenuItem(mymenu, ID_EDIT_SELECTALL, MF_BYCOMMAND | enable);
	EnableMenuItem(mymenu, ID_FORMAT_CHOOSEFONT, MF_BYCOMMAND | enable);
}
void adjustDraw(UINT enable)
{
	HMENU mymenu = GetMenu(hwndFrame());
	EnableMenuItem(mymenu, ID_DRAW_PIXEL, MF_BYCOMMAND | enable);
	EnableMenuItem(mymenu, ID_DRAW_RECTANGLE, MF_BYCOMMAND | enable);
	EnableMenuItem(mymenu, ID_DRAW_ELLIPSE, MF_BYCOMMAND | enable);
	EnableMenuItem(mymenu, ID_DRAW_LINE, MF_BYCOMMAND | enable);
}

void Upcase(TCHAR *name)
{
	for (int i = 0; i < _tcslen(name); ++i)
		name[i] = _totupper(name[i]);
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
	static int ctext = 0;
	static int cdraw = 0;
	HWND focusWin = GetFocus();
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
		case ID_WINDOW_TILEHORIZONTAL:
		{
			SendMessage(hwndMDIClient(), WM_MDITILE, MDITILE_HORIZONTAL, 0);
			break;
		}
		case ID_WINDOW_TILEVERTICLE:
		{
			SendMessage(hwndMDIClient(), WM_MDITILE, MDITILE_VERTICAL, 0);
			break;
		}
		case ID_WINDOW_CASCADE:
		{
			SendMessage(hwndMDIClient(), WM_MDICASCADE, MDITILE_ZORDER|MDITILE_SKIPDISABLED, 0);
			break;
		}
		case ID_WINDOW_CLOSEALL:
			EnumChildWindows(hwndMDIClient(),
				(WNDENUMPROC)MDICloseProc, 0L);
			break;
		case ID_DRAW_ELLIPSE:
		{
			int* currentShape = (int*)GetWindowLong(focusWin, 8);
			*currentShape = MYELLIPSE;
			break;
		}

		case ID_DRAW_LINE:
		{
			int* currentShape = (int*)GetWindowLong(focusWin, 8);
			*currentShape = MYLINE;
			break;
		}

		case ID_DRAW_RECTANGLE:
		{
			int* currentShape = (int*)GetWindowLong(focusWin, 8);
			*currentShape = MYRECT;
			break;
		}

		case ID_DRAW_PIXEL:
		{
			int* currentShape = (int*)GetWindowLong(focusWin, 8);
			*currentShape = MYPIXEL;
			break;
		}
		
	
		case ID_FILE_NEWTEXT:
		{
			TCHAR title[50];
			++ctext;
			_stprintf_p(title, 50, L"Text %d", ctext);
			HWND temp = myWinManager::addChildWindow(hwndMDIClient(), hInst, L"MDI_TEXT_CHILD", title, 0);
			return DefFrameProc(hWnd, hwndMDIClient(), message, wParam, lParam);
		}
		case ID_FILE_NEWBITMAP:
		{
			TCHAR title[50];
			++cdraw;
			_stprintf_p(title, 50, L"Bitmap %d", cdraw);
			HWND temp = myWinManager::addChildWindow(hwndMDIClient(), hInst, L"MDI_DRAW_CHILD", title, 0);
			return DefFrameProc(hWnd, hwndMDIClient(), message, wParam, lParam);
		}
		
		case ID_FORMAT_CHOOSEFONT:
		{
			HWND temp = GetFocus();
			TCHAR name[50];
			GetClassName(temp, name, 50);
			Upcase(name);
			if (_tcscmp(name, L"EDIT") == 0)
			{
				//HWND *tmp = (HWND*)GetWindowLong(temp, 0);
				temp = GetParent(temp);
			}
			CHOOSEFONT cf; // CTDL dùng cho dialog ChooseFont
			LOGFONT lf; // CTDL font, lưu kết quả font được chọn
			HFONT hfNew, hfOld;
			// Khởi tạo struct
			ZeroMemory(&cf, sizeof(CHOOSEFONT));
			cf.lStructSize = sizeof(CHOOSEFONT);
			cf.hwndOwner = hWnd; // handle của window cha
			cf.lpLogFont = &lf;
			cf.Flags = CF_SCREENFONTS | CF_EFFECTS;
			
			if (ChooseFont(&cf)) {
				// Xử lý font được chọn, vd. tạo font handle, dùng để
				hfNew = CreateFontIndirect(cf.lpLogFont); 
				HFONT gg;
				COLORREF* co = (COLORREF*)GetWindowLong(temp, 0);
				*co = cf.rgbColors;				
				SendMessage(temp, WM_SETFONT, (WPARAM)hfNew, true);
				
			}
			return DefFrameProc(hWnd, hwndMDIClient(), message, wParam, lParam);
		}

		case ID_FORMAT_CHOOSECOLOR:
		{
			HWND temp = GetFocus();
			TCHAR name[50];
			GetClassName(temp, name, 50);
			Upcase(name);
			if (_tcscmp(name, L"EDIT") == 0)
			{
				//HWND *tmp = (HWND*)GetWindowLong(temp, 0);
				temp = GetParent(temp);
			}

			CHOOSECOLOR cc; // CTDL dùng cho dialog ChooseColor
			COLORREF acrCustClr[16]; // Các màu do user định nghĩa
			DWORD rgbCurrent = RGB(255, 0, 0); // màu được chọn default
			// Khởi tạo struct
			ZeroMemory(&cc, sizeof(CHOOSECOLOR));
			cc.lStructSize = sizeof(CHOOSECOLOR);
			cc.hwndOwner = hWnd; // handle của window cha
			cc.lpCustColors = (LPDWORD)acrCustClr;
			cc.rgbResult = rgbCurrent; // trả về màu được chọn
			cc.Flags = CC_FULLOPEN | CC_RGBINIT;
			if (ChooseColor(&cc))
			{
				COLORREF* co = (COLORREF*)GetWindowLong(temp, 0);
				*co = cc.rgbResult;
				InvalidateRect(temp, 0, true);
				UpdateWindow(temp);
				
			}
			
		}
		default:
			return DefFrameProc(hWnd, hwndMDIClient(), message, wParam, lParam);
		}
	
		break;
	case WM_MENUSELECT:
	{
		HWND cur = GetFocus();
		TCHAR name[50];
		GetClassName(cur, name, 50);
		for (int i = 0; i < _tcslen(name); ++i)
			name[i] = _totupper(name[i]);
		if (_tcscmp(name, L"EDIT") == 0 || _tcscmp(name, L"MDI_TEXT_CHILD") == 0)
		{			
			adjustEdit(MF_ENABLED);
			adjustDraw(MF_GRAYED);
		}
		else
			if (_tcscmp(name, L"MDI_DRAW_CHILD") == 0)
			{
				adjustEdit(MF_GRAYED);
				adjustDraw(MF_ENABLED);
			}
			else
			{
				adjustEdit(MF_GRAYED);
				adjustDraw(MF_GRAYED);
			}
		return DefFrameProc(hWnd, hwndMDIClient(), message, wParam, lParam);
	}
	case WM_CREATE:
	{
		
		//

		CLIENTCREATESTRUCT ccs;
		ccs.hWindowMenu = GetSubMenu(GetMenu(hWnd), WINDOW_MENU_POS);
		ccs.idFirstChild = ID_FIRST_CHILD;
		hwndMDIClient() = CreateWindow(L"MDICLIENT", 0, WS_CHILD | WS_CLIPCHILDREN | WS_VSCROLL | WS_HSCROLL,
			0, 0, 0, 0, hWnd, 0, hInst, (LPSTR)&ccs);
		ShowWindow(hwndMDIClient(), SW_SHOW);
		return DefFrameProc(hWnd, hwndMDIClient(), message, wParam, lParam);
	}
	case WM_SETFOCUS:
	{
		adjustEdit(MF_GRAYED);
		adjustDraw(MF_GRAYED);
		return DefFrameProc(hWnd, hwndMDIClient(), message, wParam, lParam);
	}
	case WM_SIZE:
	{
		UINT w = LOWORD(lParam);
		UINT h = HIWORD(lParam);
		MoveWindow(hwndMDIClient(), 0, 0, w, h, true);
		return DefFrameProc(hWnd, hwndMDIClient(), message, wParam, lParam);
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
		return DefFrameProc(hWnd, hwndMDIClient(), message, wParam, lParam);
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

LRESULT CALLBACK MDICloseProc(HWND hMDIWnd, LPARAM lParam)
{
	SendMessage(hwndMDIClient(), WM_MDIDESTROY,
		(WPARAM)hMDIWnd, 0L);
	return 1;
}