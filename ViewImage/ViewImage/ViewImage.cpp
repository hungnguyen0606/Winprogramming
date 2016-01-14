// ViewImage.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "ViewImage.h"
#include <Shlobj.h>
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
//my notification
#define WM_MYDRAW (WM_USER+1)
//mytype
struct DATA
{
	int index;
	DATA()
	{
		this->index = 0;
	}
};
struct myRESULT
{
	int index;
	//đã duyệt hết ảnh hay chưa?
	bool isReady;
	int _Count;
	TCHAR path[1024], fname[1024];
	int W, H;
	HBITMAP current;
	myRESULT()
	{
		this->current = NULL;
		this->isReady = false;
		this->W = this->H = this->_Count = 0;
		this->path[0] = 0;

	}
};

//My variable

HWND global; //global window's handle
TCHAR path1[1024], path2[1024];
myRESULT lKq[2];
//
void fitToWindow(HDC hdc, HBITMAP& img, RECT rect);
void viewImgThread(LPVOID data);
void getSizeBM(HBITMAP& img, int& W, int& H);
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
	LoadString(hInstance, IDC_VIEWIMAGE, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// Perform application initialization:
	if (!InitInstance (hInstance, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_VIEWIMAGE));

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
	wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_VIEWIMAGE));
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= MAKEINTRESOURCE(IDC_VIEWIMAGE);
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
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			break;
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
		case IDD_VIEWIMG:
		{
			lKq[0].index = 0;
			lKq[1].index = 1;
			CreateThread(NULL, 1024, (LPTHREAD_START_ROUTINE)viewImgThread, &lKq[0], 0, NULL);
			CreateThread(NULL, 1024, (LPTHREAD_START_ROUTINE)viewImgThread, &lKq[1], 0, NULL);
			break;
		}
		case IDD_CHOOSE1:
		{
			// , pt[1024];
			path1[0] = 0;
			BROWSEINFO br;
			br.hwndOwner = hWnd;
			br.pidlRoot = NULL;
			br.pszDisplayName = NULL;
			br.lpfn = NULL;
			br.lpszTitle = NULL;
			br.ulFlags = 0;
			PCIDLIST_ABSOLUTE id;
			id = SHBrowseForFolder(&br);
			SHGetPathFromIDList(id, path1);
			if (id != NULL)
			{
				//Edit_SetText(GetDlgItem(hDlg, IDC_DESTINATION), path);
			}
			InvalidateRect(hWnd, 0, TRUE);
			UpdateWindow(hWnd);
			
			//viewImgThread(&lKq[0]);
			break;
		}
		case IDD_CHOOSE2:
		{
			path2[0] = 0;
			BROWSEINFO br;
			br.hwndOwner = hWnd;
			br.pidlRoot = NULL;
			br.pszDisplayName = NULL;
			br.lpfn = NULL;
			br.lpszTitle = NULL;
			br.ulFlags = 0;
			PCIDLIST_ABSOLUTE id;
			id = SHBrowseForFolder(&br);
			SHGetPathFromIDList(id, path2);
			if (id != NULL)
			{
				//Edit_SetText(GetDlgItem(hDlg, IDC_DESTINATION), path);
			}
			InvalidateRect(hWnd, 0, TRUE);
			UpdateWindow(hWnd);
			break;
		}
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
		break;
	case WM_MYDRAW:
	{
		InvalidateRect(hWnd, 0, TRUE);
		UpdateWindow(hWnd);
	}
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
	{
		
		// TODO: Add any drawing code here...
		int n = 10;
		int m = 2;
		int rowKQ = 8;
		RECT clRect;
		GetClientRect(hWnd, &clRect);
		int dy = (clRect.bottom - clRect.top) / n;
		int dx = (clRect.right - clRect.left) / m;

		//Draw background
		MoveToEx(hdc, clRect.left + dx, clRect.top, 0);
		LineTo(hdc, clRect.left + dx, clRect.bottom);
		MoveToEx(hdc, clRect.left, clRect.top + dy, 0);
		LineTo(hdc, clRect.right, clRect.top + dy);

		MoveToEx(hdc, clRect.left, clRect.top + dy * rowKQ, 0);
		LineTo(hdc, clRect.right, clRect.top + dy * rowKQ);
		//Draw folder name
		RECT reFolder;
		//reFolder.top = clRect.top;
		//reFolder.bottom = clRect.bottom;
		//reFolder.
		reFolder = clRect;
		reFolder.bottom = reFolder.top + dy;
		reFolder.right = reFolder.left + dx;
		TCHAR tempFolder[1024];
		_stprintf_p(tempFolder, 1024, L"Folder %d: %s", 1, path1);
		DrawText(hdc, tempFolder, lstrlen(tempFolder), &reFolder, DT_CENTER | DT_VCENTER);
		
		reFolder.left += dx;
		reFolder.right += dx;
		_stprintf_p(tempFolder, 1024, L"Folder %d: %s", 1, path2);
		DrawText(hdc, tempFolder, lstrlen(tempFolder), &reFolder, DT_CENTER | DT_VCENTER);

		//Draw Ket qua
		TCHAR strKQ[2048];
		RECT reKQ;
		reKQ = clRect;
		reKQ.top = clRect.top + dy*rowKQ + 10;
		reKQ.right = reKQ.left + dx;
		reKQ.left += 10;
		if (lKq[0].isReady)
		{
			_stprintf_p(strKQ, 2048, L"Kết quả:\nTổng số ảnh có trong Folder: %d\nẢnh có kích thước lớn nhất: %s\nKichs thước: %d, %d", lKq[0]._Count, lKq[0].fname, lKq[0].W, lKq[0].H);
			DrawText(hdc, strKQ, lstrlen(strKQ), &reKQ, DT_LEFT | DT_VCENTER);
		}
		reKQ.left += dx;
		reKQ.right += dx;
		if (lKq[1].isReady)
		{
			_stprintf_p(strKQ, 2048, L"Kết quả:\nTổng số ảnh có trong Folder: %d\nẢnh có kích thước lớn nhất: %s\nKichs thước: %d, %d", lKq[1]._Count, lKq[1].fname, lKq[1].W, lKq[1].H);
			DrawText(hdc, strKQ, lstrlen(strKQ), &reKQ, DT_LEFT | DT_VCENTER);
		}
		//Draw Image
		//StretchBlt()

		RECT reIMG;
		reIMG = clRect;
		reIMG.top = reIMG.top + dy;
		reIMG.bottom = reKQ.top;
		reIMG.right = reIMG.left + dx;
		if (lKq[0].current != NULL)
			fitToWindow(hdc, lKq[0].current, reIMG);

		reIMG.left += dx;
		reIMG.right += dx;
		if (lKq[1].current != NULL)
			fitToWindow(hdc, lKq[1].current, reIMG);

		
	}
	EndPaint(hWnd, &ps);
	break;
	case WM_CREATE:
	{
		global = hWnd;
		path1[0] = 0;
		path2[0] = 0;
		break;
	}
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


void viewImgThread(LPVOID data)
{
	myRESULT* dat = (myRESULT*)(data);
	TCHAR szDir[1024], temp[1024];
	if (dat->index == 0)
		lstrcpy(szDir, path1);
	else
		lstrcpy(szDir, path2);
	lstrcpy(temp, szDir);
	int n = lstrlen(szDir);
	//szDir[n] = '*';
	//szDir[n + 1] = 0;
	lstrcat(szDir, L"\\*");
	WIN32_FIND_DATA ffd;
	LARGE_INTEGER filesize;
	//TCHAR szDir[MAX_PATH];
	size_t length_of_arg;
	HANDLE hFind = INVALID_HANDLE_VALUE;
	DWORD dwError = 0;
	int ret = 0;
	//int a = rand() % 999 + 100;
	hFind = FindFirstFile(szDir, &ffd);
	do
	{
		
		if (ffd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
		{
			//_tprintf(TEXT("  %s   <DIR>\n"), ffd.cFileName);
		}
		else
		{
	

			++dat->_Count;
			int tW, tH;
			
			/*filesize.LowPart = ffd.nFileSizeLow;
			filesize.HighPart = ffd.nFileSizeHigh;
			_tprintf(TEXT("  %s   %ld bytes\n"), ffd.cFileName, filesize.QuadPart);
			*/

			//load image
			lstrcat(temp, L"\\");
			lstrcat(temp, ffd.cFileName);
			dat->current = (HBITMAP)LoadImage(hInst, temp, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
			//

			//undo lstrcat
			temp[n] = 0;
			//
			
			//update size image

			getSizeBM(dat->current, tW, tH);
			if (tW*tH > dat->W*dat->H)
			{
				dat->W = tW;
				dat->H = tH;
				TCHAR* old = dat->fname;
				lstrcpy(dat->fname, ffd.cFileName);
			}
			//
			PostMessage(global, WM_MYDRAW, 0, 0);
			Sleep(1000);
		}
	} while (FindNextFile(hFind, &ffd) != 0);

	dat->isReady = true;
	PostMessage(global, WM_MYDRAW, 0, 0);
	ExitThread(0);
	
}

void getSizeBM(HBITMAP& img, int& W, int& H)
{
	BITMAP bm;
	GetObject(img, sizeof(BITMAP), &bm);

	W = bm.bmWidth;
	H = bm.bmHeight;
}
void fitToWindow(HDC hdc, HBITMAP& img, RECT rect)
{
	rect.top += 10;
	rect.bottom -= 10;
	rect.left += 10;
	rect.right -= 10;
	int dx = rect.right - rect.left;
	int dy = rect.bottom - rect.top;

	HDC memDC = CreateCompatibleDC(hdc);
	HBITMAP hOldbmp = (HBITMAP)SelectObject(memDC, img);
	BITMAP bm;
	
	GetObject(img, sizeof(BITMAP), &bm);
	
	//
	double ratioX, ratioY;
	ratioX = 1.0*dx / bm.bmWidth;
	ratioY = 1.0*dy / bm.bmHeight;
	double ratio = ratioY;
	if (ratioX < ratioY)
		ratio = ratioX;
	if (ratio > 1)
		ratio = 1;

	RECT nImg;
	nImg.left = nImg.top = 0;
	nImg.right = bm.bmWidth*ratio;
	nImg.bottom = bm.bmHeight*ratio;

	//

	StretchBlt(hdc, (rect.left + rect.right)/2 - nImg.right/2, (rect.top + rect.bottom)/2-nImg.bottom/2, nImg.right - nImg.left, nImg.bottom - nImg.top, memDC, 0, 0, bm.bmWidth, bm.bmHeight, SRCCOPY);
	SelectObject(memDC, hOldbmp);

	DeleteDC(memDC);
}