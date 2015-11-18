#include "stdafx.h"
#include "Resource.h"
#include "DrawWindow.h"
#include "Global.h"
#include "Shape.h"
#include <vector>




ATOM myDrawWindow::MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 12;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_H51));
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = MAKEINTRESOURCE(IDC_H51);
	wcex.lpszClassName = L"MDI_DRAW_CHILD";
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassEx(&wcex);
}

LRESULT CALLBACK	myDrawWindow::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	static int x1 = 0;
	static int y1 = 0;
	static int x2 = 0;
	static int y2 = 0;
	//static int currentShape = MYRECT;
	
	static int cwindow = 0;
	int wmId, wmEvent;
	PAINTSTRUCT ps;
	HDC hdc;
	static HWND hWndTextWin;
	hWndFrame hwndFrame;
	switch (message)
	{
	case WM_COMMAND:
		wmId = LOWORD(wParam);
		wmEvent = HIWORD(wParam);
		// Parse the menu selections:
		switch (wmId)
		{
	


		default:
			return DefMDIChildProc(hWnd, message, wParam, lParam);
		}
		break;


	case WM_CREATE:
	{
		std::vector<Shape*> *v = new std::vector<Shape*>();
		COLORREF *col = new COLORREF();
		int *currentshape = new int;
		SetWindowLong(hWnd, 0, (LONG)col);
		SetWindowLong(hWnd, 4, (LONG)v);
		SetWindowLong(hWnd, 8, (LONG)currentshape);
		return DefMDIChildProc(hWnd, message, wParam, lParam);
	}


	case WM_LBUTTONDOWN:
	{
		x1 = x2 = GET_X_LPARAM(lParam);
		y1 = y2 = GET_Y_LPARAM(lParam);
		Shape *t;
		int currentShape = *(int*)GetWindowLong(hWnd, 8);
		switch (currentShape)
		{
			case MYRECT:
			{
				t = new mRectangle;
				break;
			}
			case MYELLIPSE:
			{
				t = new mEllipse;
				break;
			}
			case MYPIXEL:
			{
				t = new mPixel;
				break;
			}
			default:
			{
				t = new mLine;
				break;
			}
		}
		t->setPos(x1, y1, x2, y2);
		std::vector<Shape*> *v = (std::vector<Shape*> *)GetWindowLong(hWnd, 4);
		v->push_back(t);
		break;
		
	}
	case WM_LBUTTONUP:
	{
		x1 = x2 = LOWORD(lParam);
		y1 = y2 = HIWORD(lParam);
		break;
	}
	case WM_MOUSEMOVE:
	{
		if (wParam & MK_LBUTTON)
		{
			x2 = GET_X_LPARAM(lParam);
			y2 = GET_Y_LPARAM(lParam);
			std::vector<Shape*> *v = (std::vector<Shape*> *)GetWindowLong(hWnd, 4);
			int currentShape = *(int*)GetWindowLong(hWnd, 8);
			if (currentShape == MYPIXEL)
			{
				mPixel *t = new mPixel();
				t->setPos(x2, y2, x2, y2);
				v->push_back(t);
			}
			else
			{
				int n = v->size();
				v->at(n - 1)->setPos(x1, y1, x2, y2);
			}
			
			//(*v)[n - 1].setPos(x1, y1, x2, y2);
			InvalidateRect(hWnd, 0, true);
			UpdateWindow(hWnd);

		}
		break;
	}

	case WM_SIZE:
	{
		UINT w = LOWORD(lParam);
		UINT h = HIWORD(lParam);
		MoveWindow(hWndTextWin, 0, 0, w, h, false);
		return DefMDIChildProc(hWnd, message, wParam, lParam);
	}
	case WM_PAINT:
	{
		hdc = BeginPaint(hWnd, &ps);
		// TODO: Add any drawing code here...
		std::vector<Shape*> *v = (std::vector<Shape*>*)GetWindowLong(hWnd, 4);
		SelectObject(hdc, GetStockObject(DC_PEN));
		COLORREF mcolor = *((COLORREF*)GetWindowLong(hWnd, 0));
		SetDCPenColor(hdc, mcolor);
		for (int i = 0; i < (*v).size(); ++i)
		{
			(*v)[i]->Draw(hdc, mcolor);
		}
		EndPaint(hWnd, &ps);
		break;
	}
		
	case WM_DESTROY:
	{
		//PostQuitMessage(0);
		std::vector<Shape*> *v = (std::vector<Shape*>*)GetWindowLong(hWnd, 4);
		for (int i = 0; i < v->size(); ++i)
			delete v->at(i);
		delete (int*)GetWindowLong(hWnd, 8);
		delete (COLORREF*)GetWindowLong(hWnd, 0);
		delete v;


		break;
	}
		
	default:
		return DefMDIChildProc(hWnd, message, wParam, lParam);
	}
	return 0;
}