// TestDelayRender.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "TestDelayRender.h"

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

void onRenderFormat(HWND hWnd, WPARAM wParam, HBITMAP currentBitmap);
void onRenderAllFormat(HWND hWnd, WPARAM wParam, HBITMAP currentBitmap);

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
	LoadString(hInstance, IDC_TESTDELAYRENDER, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// Perform application initialization:
	if (!InitInstance (hInstance, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_TESTDELAYRENDER));

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
	wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_TESTDELAYRENDER));
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= MAKEINTRESOURCE(IDC_TESTDELAYRENDER);
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

	static int x1 = 0;
	static int y1 = 0;
	static int x2 = 0;
	static int y2 = 0;
	static vector<mLine> lList;

	static HBITMAP currentBitmap = NULL;
	static bool isCopy = false;

	switch (message)
	{
	case WM_COMMAND:
		wmId    = LOWORD(wParam);
		wmEvent = HIWORD(wParam);
		// Parse the menu selections:
		switch (wmId)
		{
		case IDM_ABOUT:
			//isCopy = !isCopy;
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			break;
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
		case ID_DRAW:
		{
			isCopy = false;
			HMENU men = GetMenu(hWnd);
			EnableMenuItem(men, ID_COPY, MF_BYCOMMAND | MF_ENABLED);
			EnableMenuItem(men, ID_DRAW, MF_BYCOMMAND | MF_GRAYED);
			break;
		}
			
		case ID_COPY:
		{
			HMENU men = GetMenu(hWnd);
			EnableMenuItem(men, ID_COPY, MF_BYCOMMAND | MF_GRAYED);
			EnableMenuItem(men, ID_DRAW, MF_BYCOMMAND | MF_ENABLED);
			isCopy = true;
			break;
		}
			
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
		break;
	case WM_CREATE:
	{
		HMENU men = GetMenu(hWnd);
		EnableMenuItem(men, ID_COPY, MF_BYCOMMAND | MF_ENABLED);
		EnableMenuItem(men, ID_DRAW, MF_BYCOMMAND | MF_GRAYED);
		break;
	}
	case WM_RENDERFORMAT:
	{
		onRenderFormat(hWnd, wParam, currentBitmap);
		break;
	}
	case WM_RENDERALLFORMATS:
	{
		onRenderAllFormat(hWnd, wParam, currentBitmap);
		break;
	}
	case WM_DESTROYCLIPBOARD:
	{
		if (currentBitmap != NULL)
		{
			DeleteObject(currentBitmap);
			currentBitmap = NULL;
		}
		break;
	}
	case WM_LBUTTONDOWN:
	{
		x1 = x2 = GET_X_LPARAM(lParam);
		y1 = y2 = GET_Y_LPARAM(lParam);
		
		break;
	}

	case WM_LBUTTONUP:
	{

		if (isCopy)
		{
			
			hdc = GetDC(hWnd);
			HDC memDC = CreateCompatibleDC(hdc);
			SetROP2(hdc, R2_NOTXORPEN);
			Rectangle(hdc, min(x1, x2), min(y1, y2), max(x1, x2), max(y1, y2));
			//
			if (x1 > x2)
				std::swap(x1, x2);
			if (y1 > y2)
				std::swap(y1, y2);
			//
			
			if (currentBitmap != NULL)
				DeleteObject(currentBitmap);
			
			
			HBITMAP temp = (HBITMAP)SelectObject(memDC, CreateCompatibleBitmap(hdc, x2 - x1, y2 - y1));

			BitBlt(memDC, 0, 0, x2 - x1, y2 - y1, hdc, x1, y1, SRCCOPY);
			
			temp = (HBITMAP) SelectObject(memDC, temp);
			
			DeleteDC(memDC);
			ReleaseDC(hWnd, hdc);

			//int gg = sizeof(BITMAP);
			if (temp != NULL)
			{
				
				OpenClipboard(hWnd);
				EmptyClipboard();
				

				SetClipboardData(CF_BITMAP, NULL);
				CloseClipboard();
				
				currentBitmap = temp;
				MessageBox(hWnd, L"The Image has been copied to clipboard.", L"Copy Successfully", MB_OK);
			}
			else
			{
				MessageBox(hWnd, L"Cannot copy image to clipboard.", L"Error", MB_OK);
			}
			x1 = x2;
			y1 = y2;
		}
		else
		{
			
			

		}
		break;
	}
	case WM_MOUSEMOVE:
	{ 
		if (wParam & VK_LBUTTON)
		{
			int nx, ny;
			nx = GET_X_LPARAM(lParam);
			ny = GET_Y_LPARAM(lParam);
			hdc = GetDC(hWnd);


			if (isCopy)
			{
				hdc = GetDC(hWnd);

				SetROP2(hdc, R2_NOTXORPEN);
				Rectangle(hdc, min(x1, x2), min(y1, y2), max(x1, x2), max(y1, y2));

				Rectangle(hdc, min(x1, nx), min(y1, ny), max(x1, nx), max(y1, ny));
				ReleaseDC(hWnd, hdc);
			}
			else
			{
				
				mLine l;
				
				l.setPos(x1, y1, nx, ny);
				x1 = nx;
				y1 = ny;
				lList.push_back(l);
				InvalidateRect(hWnd, 0, TRUE);
				UpdateWindow(hWnd);
			}
			x2 = nx;
			y2 = ny;
			ReleaseDC(hWnd, hdc);
		}
		
		break;
	}
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		// TODO: Add any drawing code here...
		for (int i = 0; i < lList.size(); ++i)
			lList[i].Draw(hdc, NULL);
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

void onRenderFormat(HWND hWnd, WPARAM wParam, HBITMAP currentBitmap)
{
	if (wParam == CF_BITMAP)
	{
		HBITMAP newBitmap;
		newBitmap = (HBITMAP) CopyImage(currentBitmap, IMAGE_BITMAP, 0, 0, LR_DEFAULTSIZE);
		SetClipboardData(CF_BITMAP, newBitmap);
		//DeleteObject(newBitmap);
		
	}
}

void onRenderAllFormat(HWND hWnd, WPARAM wParam, HBITMAP currentBitmap)
{
	OpenClipboard(hWnd);
	EmptyClipboard();
	onRenderFormat(hWnd, wParam, currentBitmap);
	CloseClipboard();
}