// P3.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "P3.h"
#include <Windows.h>
#include <algorithm>
#include <functional>
#include <utility>
#include <queue>
#include <vector>
#include <list>
#include <ctime>
#define MYUP 0
#define MYDOWN 1
#define MYLEFT 2
#define MYRIGHT 3

int dx[] = { 0, 0, -1, 1 };
int dy[] = { -1, 1, 0, 0 };
using namespace std;

class myRect{
private:
	COLORREF mColor;
	int mType, direction;
	pair<int, int> pos;
public:
	myRect()
	{
		mColor = RGB(0, 0, 0);
		direction = MYRIGHT;
		mType = rand()%3;
		pos.first = -5;
		pos.second = 0;

	}

	void move()
	{
		pos.first += dx[direction];
		pos.second += dy[direction];
	}

	bool isOut()
	{
		return false;
	}

	bool isAtCheckPoint()
	{
		return pos.first == 0 && pos.second == 0;
		return false;
	}
	
	void setDirection(int dir)
	{
		direction = dir;
	}

	void setType(int type)
	{
		this->mType = type;
	}

	void setColor(COLORREF color)
	{
		mColor = color;
	}

	int getType()
	{
		return mType;
	}

	COLORREF getColor()
	{
		return mColor;
	}

	pair<int, int> getPosition()
	{
		return this->pos;
	}
};

struct data{
	myRect* rect;
	int queueType;
	bool isTrue;
};

HANDLE oriMutex;
vector<list<myRect> > q;
int total, remaining;
int cQ[3];
TCHAR nameList[][2] = { L"1", L"2", L"3" };
COLORREF colorList[3] = { RGB(255,0,0), RGB(0,255,0), RGB(0,0,255) };
int directionList[3] = { MYUP, MYRIGHT, MYDOWN };
pair<int, int> posCount[3] = { make_pair(-1, -3), make_pair(4, -1), make_pair(-1, 3) };

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
INT_PTR CALLBACK getTotal(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);
void test(LPVOID para);

void onStart(LPVOID para);
RECT calRect(RECT wndRect, pair<int, int> pos);
#define WM_MYDRAW WM_USER+1
HWND global;
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
	LoadString(hInstance, IDC_P3, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// Perform application initialization:
	if (!InitInstance (hInstance, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_P3));

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
	wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_P3));
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= MAKEINTRESOURCE(IDC_P3);
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
	static HANDLE stThread = NULL;

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
		case ID_START:
		{
			DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOG1), hWnd, getTotal);
			remaining = total;
			cQ[0] = cQ[1] = cQ[2] = 0;
			q.push_back(list<myRect>());
			q.push_back(list<myRect>());
			q.push_back(list<myRect>());
			q.push_back(list<myRect>());
			stThread = CreateThread(NULL, 1024, (LPTHREAD_START_ROUTINE)onStart, 0, 0, 0);
			//onStart(NULL);
			break;
		}
		case ID_END:
		{
			TerminateThread(stThread, 0);
			stThread = NULL;
			q.clear();
			InvalidateRect(hWnd, 0, TRUE);
			UpdateWindow(hWnd);
			break;
		}
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
		break;
	
	case WM_CREATE:
	{
		
		
		global = hWnd;
		//CreateThread(NULL, 1024, (LPTHREAD_START_ROUTINE)test, 0, 0, 0);
			break;
	}
	case WM_MYDRAW:
	{
		InvalidateRect(hWnd, 0, TRUE);
		UpdateWindow(hWnd);
		break;
	}
	case WM_PAINT:
	{
		if (stThread == NULL)
		{
			break;
		}
		//InvalidateRect(hWnd, 0, TRUE);
		//UpdateWindow(hWnd);
		hdc = BeginPaint(hWnd, &ps);
		// TODO: Add any drawing code here...
		RECT rect;
		GetClientRect(hWnd, &rect);
		pair<int, int> Oxy((rect.right - rect.left) / 2, (rect.bottom - rect.top) / 2);

		// paint background
		RECT ori = calRect(rect, make_pair(0, 0));
		ori.top -= 10;
		ori.bottom += 10;
		ori.left -= 10;
		ori.right += 10;

		MoveToEx(hdc, rect.left, ori.top, 0);
		LineTo(hdc, ori.left, ori.top);
		MoveToEx(hdc, ori.left, rect.top, 0);
		LineTo(hdc, ori.left, ori.top);
		MoveToEx(hdc, ori.right, ori.top, 0);
		LineTo(hdc, rect.right, ori.top);
		MoveToEx(hdc, ori.right, ori.top, 0);
		LineTo(hdc, ori.right, rect.top);

		MoveToEx(hdc, ori.left, ori.bottom, 0);
		LineTo(hdc, rect.left, ori.bottom);
		MoveToEx(hdc, ori.left, ori.bottom, 0);
		LineTo(hdc, ori.left, rect.bottom);
		MoveToEx(hdc, ori.right, ori.bottom, 0);
		LineTo(hdc, rect.right, ori.bottom);
		MoveToEx(hdc, ori.right, ori.bottom, 0);
		LineTo(hdc, ori.right, rect.bottom);
		//

		//start to paint rect
		int szRect, szBorder;
		HGDIOBJ origin = SelectObject(hdc, GetStockObject(DC_PEN));
		TCHAR s[30];
	//	int remaining = total;
		for (int i = 0; i < q.size(); ++i)
		{
			if (i < q.size() - 1)
			{
				RECT r = calRect(rect, posCount[i]);
				//_stprintf_p(s, 30, L"Line %d", i + 1);
				//DrawText(hdc, s, lstrlen(s), &r, DT_BOTTOM | DT_CENTER | DT_SINGLELINE);
				_stprintf_p(s, 30, L"Count = %d\nLine %d", cQ[i], i + 1);
				DrawText(hdc, s, lstrlen(s), &r, DT_VCENTER | DT_CENTER);
			}
			//remaining -= cQ[i];
			
			for (list<myRect>::iterator it = q[i].begin(); it != q[i].end(); ++it)
			{

				SetDCPenColor(hdc, it->getColor());
				RECT re = calRect(rect, it->getPosition());
				Rectangle(hdc, re.left, re.top, re.right, re.bottom);
				DrawText(hdc, nameList[it->getType()], 2, &re, DT_VCENTER | DT_CENTER | DT_SINGLELINE);
				
			}
		}

		RECT r = calRect(rect, make_pair(-4, -1));
		RECT sz;
		_stprintf_p(s, 30, L"Total = %d\nRemaining = %d", total, remaining);
		DrawText(hdc, s, lstrlen(s), &sz, DT_CALCRECT);
		r.right = r.left + sz.right - sz.left;
		r.bottom = r.top + sz.bottom - sz.top;
		DrawText(hdc, s, lstrlen(s), &r, DT_VCENTER | DT_LEFT);
		//
		EndPaint(hWnd, &ps);
	}
		
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

INT_PTR CALLBACK getTotal(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			total = GetDlgItemInt(hDlg, IDC_EDIT1, 0, false);
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}

void test(LPVOID para)
{
	//SendMessage(global, MY_NOTI, 0, 0);
	return;
}
void checkBox(LPVOID para)
{
	WaitForSingleObject(oriMutex, 2000);
	data *dat = (data*)para;
	dat->isTrue = dat->rect->getType() == dat->queueType;
	COLORREF temp = dat->rect->getColor();
	dat->rect->setColor(colorList[dat->queueType]);
	PostMessage(global, WM_MYDRAW, 0, 0);
	Sleep(1000);
	ReleaseMutex(oriMutex);
	ExitThread(0);
}
void onStart(LPVOID para)
{
	srand(time(NULL));
	HANDLE threadHandle[3];
	data dat[3];
	int sz = 3;
	//int num = 10;
	bool isEnd = false;
	while (!isEnd)
	{
		int cc = 0;
		myRect temp;
		//temp.setType(num);
		if (remaining > 0)
		{
			q[q.size() - 1].push_back(temp);
			--remaining;
		}
		
		for (int i = 0; i < q.size(); ++i)
		{
			cc += q[i].size();
			for (list<myRect>::iterator it = q[i].begin(); it != q[i].end(); ++it)
				it->move();
			while (!q[i].empty() && q[i].begin()->isOut())
				q[i].pop_front();
		}
		PostMessage(global, WM_MYDRAW, 0, 0); 
		Sleep(1000);
		
		if (q[q.size() - 1].size())
		if (q[q.size()-1].begin()->isAtCheckPoint())
		{
			
			for (int i = 0; i < sz; ++i)
			{
				
				dat[i].rect = &(*q[q.size() - 1].begin());
				dat[i].queueType = i;
				dat[i].isTrue = false;
				threadHandle[i] = CreateThread(NULL, 1024, (LPTHREAD_START_ROUTINE)checkBox, &dat[i], 0, 0);
			}

			oriMutex = CreateMutex(NULL, false, NULL);
			bool state = WaitForMultipleObjects(sz, threadHandle, TRUE, INFINITE);
			CloseHandle(oriMutex);

			for (int i = 0; i < sz; ++i)
				if (dat[i].isTrue)
				{
					++cQ[i];
					myRect temp(*q[q.size() - 1].begin());
					temp.setDirection(directionList[i]);
					temp.setColor(colorList[i]);

					q[i].push_back(temp);
					q[q.size() - 1].pop_front();
					break;
				}
				
		}
	
		isEnd = cc == 0;
	}
	
	ExitThread(0);
}

RECT calRect(RECT wndRect, pair<int, int> pos)
{
	RECT ret;
	int dx = (wndRect.right - wndRect.left) / 9;
	int dy = (wndRect.bottom - wndRect.top) / 7;
	ret.left = (dx*(pos.first + 4));
	ret.top = (dy*(pos.second + 3));
	ret.right = ret.left + dx - 10;
	ret.bottom = ret.top + dy - 10;
	ret.left += 10;
	ret.top += 10;
	return ret;
}