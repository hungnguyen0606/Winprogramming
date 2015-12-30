// H14.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "H14.h"
#include <Windowsx.h>
#include <Shlwapi.h>
#include <commdlg.h>
#include <Shlobj.h>
#include <cstdio>
#include <malloc.h>
#include <string>

#include "func.h"

using namespace std;
#define MAX_LOADSTRING 100
#define  MY_WM_NOTIFYICON  WM_USER+1
// Global Variables:
HINSTANCE hInst;								// current instance
TCHAR szTitle[MAX_LOADSTRING];					// The title bar text
TCHAR szWindowClass[MAX_LOADSTRING];			// the main window class name

// Forward declarations of functions included in this code module:
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	About(HWND, UINT, WPARAM, LPARAM);
//-------------------------------------------------
HWND global;
int getFileNamePos(TCHAR* path);
void copyTo(LPVOID dat);
bool isValidPath(TCHAR path[]);
bool mergeFiles();
char* tcharToChar(TCHAR* s);
bool mergeFiles(string des, string filename);
INT_PTR CALLBACK CopyDialog(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);
//----------------------------------------------------
int idStatic[] = { IDC_STATIC_1, IDC_STATIC_2, IDC_STATIC_3, IDC_STATIC_4, IDC_STATIC_5 };
int lx[] = { 100, 150, 200, 250, 300 };
int ly[] = { 200, 200, 200, 200, 200 };

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
	LoadString(hInstance, IDC_H14, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// Perform application initialization:
	if (!InitInstance (hInstance, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_H14));

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
	wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_H14));
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= MAKEINTRESOURCE(IDC_H14);
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
		DialogBox(hInst, MAKEINTRESOURCE(IDD_COPY), hWnd, CopyDialog);
		SendMessage(hWnd, WM_DESTROY, 0, 0);
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

INT_PTR CALLBACK CopyDialog(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
	{
		//getdlgi
		global = hDlg;
		RECT rect;
		GetWindowRect(hDlg, &rect);
		for (int i = 0; i < 5; ++i)
		{

			GetWindowRect(GetDlgItem(hDlg, IDC_SOURCE), &rect);
			int yy;
		}
			return (INT_PTR)TRUE;
	}
		
	case MY_WM_NOTIFYICON:
	{
		SetWindowText(GetDlgItem(hDlg, idStatic[0]), L"Hello");
		break;
	}
	case WM_COMMAND:
	{
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}

		switch (LOWORD(wParam))
		{
		case IDC_BUTTON_SOURCE:
		{
			OPENFILENAME ofn; // CTDL dùng cho dialog open
			TCHAR szFile[1024];
			//TCHAR *szFilter = NULL;
			szFile[0] = '\0';
			// Khởi tạo struct
			ZeroMemory(&ofn, sizeof(OPENFILENAME));
			ofn.lStructSize = sizeof(OPENFILENAME);
			ofn.hwndOwner = hDlg; // handle của window cha
			ofn.lpstrFilter = NULL;
			ofn.nFilterIndex = 1;
			ofn.lpstrFile = szFile; // chuỗi tên file trả về
			ofn.nMaxFile = sizeof(szFile);
			ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;
			BOOL a;
			a = GetOpenFileName(&ofn);
			if (a)
			{
				Edit_SetText(GetDlgItem(hDlg, IDC_SOURCE), szFile);
			}
			break;
		}
		
		case IDC_BUTTON_DESTINATION:
		{
			TCHAR path[1024];// , pt[1024];
			path[0] = 0;
			BROWSEINFO br;
			br.hwndOwner = hDlg;
			br.pidlRoot = NULL;
			br.pszDisplayName = NULL;
			br.lpfn = NULL;
			br.lpszTitle = NULL;
			br.ulFlags = 0;
			PCIDLIST_ABSOLUTE id;
			id = SHBrowseForFolder(&br);
			SHGetPathFromIDList(id, path);
			if (id != NULL)
			{
				Edit_SetText(GetDlgItem(hDlg, IDC_DESTINATION), path);
			}
			break;
		}
		case IDC_BUTTON_COPY:
		{
			data dat[5];
			TCHAR source[1024], destination[1024];
			char fname[1024];

			HANDLE threadHandle[5];
			int threadId[5];
			GetDlgItemText(hDlg, IDC_SOURCE, source, 1023);
			GetDlgItemText(hDlg, IDC_DESTINATION, destination, 1023);
			int numThread = 0;

			//error handle
			if (!isValidPath(source) || (GetFileAttributes(source)&FILE_ATTRIBUTE_DIRECTORY))
			{
				MessageBox(hDlg, L"Invalid file.", L"Error", MB_OK);
				break;
			}

			if (!isValidPath(destination) || (GetFileAttributes(destination)&FILE_ATTRIBUTE_DIRECTORY)==0)
			{
				MessageBox(hDlg, L"Invalid destination folder.", L"Error", MB_OK);
				break;
			}
			numThread = (int)GetDlgItemInt(hDlg, IDC_NUMTHREAD, 0, TRUE);
			if (numThread < 1 || numThread > 5)
			{
				MessageBox(hDlg, L"The number of threads must be between 1-5.", L"Error", MB_OK);
				break;
			}
			int fileNamePos = getFileNamePos(source);
			//-------
			char *ss, *dd;
			ss = tcharToChar(source);
			dd = tcharToChar(destination);
			 
			FILE* fi = fopen(ss, "rb");
			int fileSize = calcFileSize(fi);
			fclose(fi);
			int ave = fileSize / numThread;
			for (int i = 0; i < numThread; ++i)
			{
				dat[i].size = ave;
				if (i == numThread - 1)
					dat[i].size = ALL;
				dat[i].posx = lx[i];
				dat[i].posy = ly[i];
				dat[i].offset = i*ave;
				dat[i].idViewer = GetDlgItem(hDlg, idStatic[i]);
				dat[i].source = string(ss);
				dat[i].destination = string(dd);
				sprintf(fname, "%s.%02d", ss + fileNamePos, i + 1);
				dat[i].filename = string(fname);

				threadHandle[i] = CreateThread(NULL, 1024, (LPTHREAD_START_ROUTINE)copyTo, &dat[i], 0, (LPDWORD) &threadId[i]);
				if (threadHandle[i] == NULL)
				{
					MessageBox(hDlg, L"Cannot create enough threads to copy.", L"Error", MB_OK);
					return (INT_PTR)TRUE;
				}
			}

			DWORD Status = WaitForMultipleObjects(numThread, threadHandle, TRUE, INFINITE);
			bool isMerged = mergeFiles(string(dd), string(ss+fileNamePos));

			SetWindowText(GetDlgItem(hDlg, IDC_STATIC_1), L"Joining files...");
			//InvalidateRect(hDlg, NULL, TRUE);
			//UpdateWindow(hDlg);
			if (!isMerged)
			{
				MessageBox(hDlg, L"Fail to merge files.", L"Error", MB_OK);
			}
			else
			{
				MessageBox(hDlg, L"Copy successfully.", L"Error", MB_OK);
			}
			SetWindowText(GetDlgItem(hDlg, IDC_STATIC_1), L"");
			InvalidateRect(hDlg, NULL, TRUE);
			UpdateWindow(hDlg);
			break;
		}
		

		default: return (INT_PTR)FALSE;
		}
		break;
	}
		
	}
	return (INT_PTR)FALSE;
}

char* tcharToChar(TCHAR* s)
{
	int n = lstrlen(s);
	char* ret = new char[n + 1];
	for (int i = 0; i <= n; ++i)
		ret[i] = (char)s[i];
	return ret;
}
int getFileNamePos(TCHAR* path)
{
	int n = lstrlen(path);
	if (n < 1)
		return NULL;
	TCHAR* ret = NULL;
	while (--n >= 0)
	{
		if (path[n] == '\\' || path[n] == '/')
			return n+1;
	}
}
int getNumThread(HWND hDlg)
{
//	HWND combo = GetDlgItem(hDlg, IDC_COMBO_THREAD);
	return 0;
}
void copyTo(LPVOID dat)
{
	data &mdat = *((data*)dat);
	FILE *s, *d;
	HDC dc = GetDC(global);
	//TextOut(dc, 0, 0, L"Hello", 6);
	s = fopen(mdat.source.c_str(), "rb");
	d = fopen((mdat.destination+"\\"+mdat.filename).c_str(), "wb");
	fseek(s, mdat.offset, SEEK_SET);
	copyPartFile(s, d, mdat.size, global, &mdat);
	ReleaseDC(global, dc);
	fclose(s);
	fclose(d);
	ExitThread(0);
}

bool mergeFiles(string des, string filename)
{
	bool a = joinFile((des + "\\" + filename).c_str()) == 0;
	return a;
}

bool isValidPath(TCHAR path[])
{
	return PathFileExists(path);
	return true;
}