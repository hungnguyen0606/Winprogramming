// ----------------------------------------------------------------------
//           Minh hoa thao tac dua App vao Status Area
//               Thiet ke tren API
//               GENERIC_APP.CPP
//			 Nguyen Tri Tuan - Khoa CNTT - DHKHTN
// --------------------------------------------------------------------------
// - Khi user nhan Minimize (xu ly message WM_SIZE voi wParam=SIZE_MINIMIZED
//   thi se Hide cua so, dong thoi Add icon vao System Tray cua Taskbar.
//   Cua so hWnd duoc chi dinh se nhan message Callback tu Icon tren 
//   System Tray.
// - Khi user Click mouse tren Tray-Icon (phat sinh message MY_WM_NOTIFYICON)
//   se restore cua so Frame
// - Cac ham xu ly quan trong:
//	+ MyTaskBarAddIcon: them icon vao System Tray
//	+ MyTaskBarDeleteIcon: delete icon khoi System tray
//	+ doMyNotify: xu ly cho message MY_WM_NOTIFYICON 
//	  (khi user click len icon trong System tray)
// --------------------------------------------------------------------------

#include "stdafx.h"
#include <shellapi.h>
#include "resource.h"

#define MAX_LOADSTRING 100

// Dinh nghia message se duoc send cho Window khi user tac dong len Tray-Icon
#define  MY_WM_NOTIFYICON  WM_USER+1
// Dinh nghia ID cua Icon tren Status Area
#define  TRAY_ICON_ID		   1	

// Global Variables:
HINSTANCE hInst;								// current instance
TCHAR szTitle[MAX_LOADSTRING];					// The title bar text
TCHAR szWindowClass[MAX_LOADSTRING];			// the main window class name

// Forward declarations of functions included in this code module:
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	About(HWND, UINT, WPARAM, LPARAM);

void  doMinimize(HWND hWnd);
void doSize(HWND hWnd, WPARAM wParam);
void doMyNotify(HWND hWnd, WPARAM wParam, LPARAM lParam);
BOOL MyTaskBarAddIcon(HWND hWnd, UINT uID, HICON hIcon, LPCWSTR lpszTip);
BOOL MyTaskBarDeleteIcon(HWND hWnd, UINT uID);

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
	LoadString(hInstance, IDC_SYSTEM_TRAY, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// Perform application initialization:
	if (!InitInstance (hInstance, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_SYSTEM_TRAY));

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
	wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_SYSTEM_TRAY));
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= MAKEINTRESOURCE(IDC_SYSTEM_TRAY);
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
		case IDM_ABOUT:
			MessageBox(hWnd, 
				L"System Tray Demo \nNhan Minimize button de dua App vao System Tray\nClick mouse tren Icon de retore App.",
				L"Gioi thieu", MB_OK);
			break;
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
		break;
	case WM_SIZE:
		doSize(hWnd, wParam);
		break;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		// TODO: Add any drawing code here...
		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case MY_WM_NOTIFYICON:
		doMyNotify(hWnd, wParam, lParam);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

//  ---------------------------------------------------------------------
//    doMinimize Function
//      Ham xu ly khi user nhan nut Minimize
//		- App se bi Hidden
//		- Add icon vao Status Area cua Taskbar
//  ---------------------------------------------------------------------
void  doMinimize(HWND hWnd)
{
	ShowWindow(hWnd, SW_HIDE);

	HICON hIcon = LoadIcon(hInst, MAKEINTRESOURCE(IDI_ICON));

	MyTaskBarAddIcon(hWnd, TRAY_ICON_ID, hIcon, (LPCWSTR) L"Demo App. Click to restore !");
}

//  ---------------------------------------------------------------------
//    doSizeFrame Function
//     Ham xu ly khi co thay doi kich thuoc cua so 
//  ---------------------------------------------------------------------
void doSize(HWND hWnd, WPARAM wParam)
{
	if (wParam==SIZE_MINIMIZED)  doMinimize(hWnd);
}

//  ---------------------------------------------------------------------
//    doMyNotify Function
//     Ham xu ly khi user thao tac tren Icon cua Status Area
//	   - Restore cua so Frame
//	   - Xoa icon tren Status Area	
//  ---------------------------------------------------------------------
void doMyNotify(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
	if (lParam==WM_LBUTTONDOWN) {

		 MyTaskBarDeleteIcon(hWnd, TRAY_ICON_ID);
		
		ShowWindow(hWnd, SW_SHOW);

		ShowWindow(hWnd, SW_RESTORE);
	}
}

// -----------------------------------------------------------------
// MyTaskBarAddIcon - Them icon vao Status Area cua Taskbar 
// Ket qua tra ve: TRUE neu thanh cong; FALSE neu khong thanh cong
// hWnd - handle cua Window se nhan thong diep CallBack 
// uID - identifier cua icon se them
// hicon - handle cua icon dung de them 
// lpszTip - ToolTip text (xuat hien tren icon khi user dua mouse vao icon)
// -----------------------------------------------------------------
BOOL MyTaskBarAddIcon(HWND hWnd, UINT uID, HICON hIcon, LPCWSTR lpszTip)
{
	BOOL Kq;
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

	Kq = Shell_NotifyIcon(NIM_ADD, &tnid);

	if (hIcon)
		DestroyIcon(hIcon);

	return Kq;
}

// -----------------------------------------------------------------
// MyTaskBarDeleteIcon - Xoa icon tren Status Area cua Taskbar 
// Ket qua tra ve: TRUE neu thanh cong; FALSE neu khong thanh cong 
// hWnd - handle cua Window da Add icon vao Status Area
// uID - identifier cua Icon se bi xoa 
// -----------------------------------------------------------------
BOOL MyTaskBarDeleteIcon(HWND hWnd, UINT uID)
{
	BOOL Kq;
	NOTIFYICONDATA tnid;

	tnid.cbSize = sizeof(NOTIFYICONDATA);
	tnid.hWnd = hWnd;
	tnid.uID = uID;

	Kq = Shell_NotifyIcon(NIM_DELETE, &tnid);
	return Kq;
}

