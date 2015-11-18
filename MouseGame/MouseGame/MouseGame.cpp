// MouseGame.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include <process.h>
#include "MouseGame.h"
#include <commdlg.h>
#include <Windowsx.h>
//#include <stdio.h>
//#include <stdlib.h>
//#include <time.h>


#define MAX_LOADSTRING 300

struct MyImage {
	int x, y;
	HANDLE h, h2;
	int ok;
	int ww, hh;
} img[500];

int kill = 0;

int cl = 0;
int timing = 0, nmouse = 0;
// Global Variables:
HINSTANCE hInst;								// current instance
TCHAR szTitle[MAX_LOADSTRING];					// The title bar text
TCHAR szWindowClass[MAX_LOADSTRING];			// the main window class name
TCHAR liveFile[MAX_LOADSTRING], deadFile[MAX_LOADSTRING];
TCHAR aaa[] = TEXT("C:\\Users\\Dell\\Desktop\\a.bmp");
TCHAR bbb[] = TEXT("C:\\Users\\Dell\\Desktop\\b.bmp");
// Forward declarations of functions included in this code module:
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY _tWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPTSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	// TODO: Place code here.
	//srand(time(NULL));
	MSG msg;
	HACCEL hAccelTable;

	// Initialize global strings
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_MOUSEGAME, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// Perform application initialization:
	if (!InitInstance(hInstance, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_MOUSEGAME));

	// Main message loop:
	while (GetMessage(&msg, NULL, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return (int)msg.wParam;
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

	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_MOUSEGAME));
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = MAKEINTRESOURCE(IDC_MOUSEGAME);
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

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

INT_PTR CALLBACK DiaProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	TCHAR szFilter[] = TEXT("BMP file\0*.BMP\0");
	TCHAR szFile[256], szFile2[256], buffer[256];
	switch (message)
	{
	case WM_COMMAND:
		int wmId;
		wmId = LOWORD(wParam);
		switch (wmId)
		{
		case IDC_BUTTON_LOAD_LIVE:
		case IDC_BUTTON_LOAD_DEAD:
			OPENFILENAME ofn; // CTDL dùng cho dialog open

			szFile[0] = '\0';
			// Khởi tạo struct
			ZeroMemory(&ofn, sizeof(OPENFILENAME));
			ofn.lStructSize = sizeof(OPENFILENAME);
			ofn.hwndOwner = hDlg; // handle của window cha
			ofn.lpstrFilter = szFilter;
			ofn.nFilterIndex = 1;
			ofn.lpstrFile = szFile; // chuỗi tên file trả về
			ofn.nMaxFile = sizeof(szFile);
			ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;
			BOOL a;
			a = GetOpenFileName(&ofn);
			if (a)
			{
				if (wmId == IDC_BUTTON_LOAD_LIVE) {
					Edit_SetText(GetDlgItem(hDlg, IDC_EDIT3), szFile);
				}
				else
					Edit_SetText(GetDlgItem(hDlg, IDC_EDIT4), szFile);
			}

			break;

		case IDOK:
			Edit_GetText(GetDlgItem(hDlg, IDC_EDIT3), liveFile, 256);
			Edit_GetText(GetDlgItem(hDlg, IDC_EDIT4), deadFile, 256);
			Edit_GetText(GetDlgItem(hDlg, IDC_EDIT1), buffer, 256);
			timing = _ttoi(buffer);
			Edit_GetText(GetDlgItem(hDlg, IDC_EDIT2), buffer, 256);
			nmouse = _ttoi(buffer);
			EndDialog(hDlg, (INT_PTR)TRUE);

			break;
		}
		break;

	case WM_CLOSE:
		PostQuitMessage(0);
		return (INT_PTR)TRUE;
	}
	return (INT_PTR)FALSE;
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
bool inside(int x, int y, MyImage im)
{
	if (x >= im.x && y >= im.y && x <= im.x + im.ww && y <= im.y + im.hh)
		return true;
	return false;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	PAINTSTRUCT ps;
	HDC hdc;
	static int nim = 0;
	static int cx, cy;
	static int c = 0;
	switch (message)
	{
	case WM_SIZE:
		cx = LOWORD(lParam);
		cy = HIWORD(lParam);
		break;

	case WM_CREATE:
		break;

	case WM_TIMER:
		nim = 0;
		c += 1;
		for (int i = 0; i < nmouse; ++i)
		{
			HANDLE h;
			img[nim].h = LoadImage(hInst, liveFile, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
			img[nim].h2 = LoadImage(hInst,deadFile, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
			int x, y;
			x = rand() % cx;
			y = rand() % cy;
			img[nim].x = x;
			img[nim].y = y;
			img[nim].ok = 0;
			nim++;
		}
		InvalidateRect(hWnd, NULL, TRUE);
		UpdateWindow(hWnd);

		break;

	case WM_COMMAND:
		wmId = LOWORD(wParam);
		wmEvent = HIWORD(wParam);
		// Parse the menu selections:
		switch (wmId)
		{
		case ID_START:
			SetTimer(hWnd, 333, timing, TIMERPROC(NULL));
			break;

		case ID_END:
			KillTimer(hWnd, 333);
			TCHAR buffer[500];
			_stprintf_p(buffer, 500, TEXT("So chuot chet %d"), kill);
			MessageBox(hWnd, buffer, TEXT(""), MB_OK);
			nmouse = 0;
			nim = 0;
			kill = 0;

			break;

		case ID_SETTINGS:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOG1), hWnd, DiaProc);
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

	case WM_LBUTTONDOWN:
		int x, y;
		x = LOWORD(lParam);
		y = HIWORD(lParam);
		if (c >= 2)
		{
			int a;
			a = 1;
		}
		for (int i = 0; i < nim; ++i)
		{
			if (img[i].ok == 0)
				if (inside(x, y, img[i]))
				{
					img[i].ok = -1;
					kill++;
					
				}
		}
		InvalidateRect(hWnd, NULL, TRUE);
		UpdateWindow(hWnd);
		break;

	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		// TODO: Add any drawing code here...
		//hdc = GetDC(hWnd);

		HDC hdcMem;
		hdcMem = CreateCompatibleDC(hdc);

		BITMAP bitmap;
		for (int i = 0; i < nim; ++i)
			{
				HANDLE tmp;
				tmp = img[i].h;
				if (img[i].ok == -1)
					tmp = img[i].h2;
				SelectObject(hdcMem, tmp);
				GetObject(tmp, sizeof(bitmap), &bitmap);
				BitBlt(hdc, img[i].x, img[i].y, bitmap.bmWidth, bitmap.bmHeight, hdcMem, 0, 0, SRCCOPY);
				img[i].ww = bitmap.bmWidth;
				img[i].hh = bitmap.bmHeight;
			}
		DeleteDC(hdcMem);

		//ReleaseDC(hWnd, hdc);

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
