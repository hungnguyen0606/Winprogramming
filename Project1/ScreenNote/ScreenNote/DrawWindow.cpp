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
	wcex.hIcon = 0;
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = 0;
	wcex.lpszClassName = L"DRAW_WINDOW";
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassEx(&wcex);
}

LRESULT CALLBACK	myDrawWindow::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	static vector<Shape*>* allShape;
	static PoolShape myPool;
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

	switch (message)
	{
	case WM_COMMAND:
		wmId = LOWORD(wParam);
		wmEvent = HIWORD(wParam);
		// Parse the menu selections:
		switch (wmId)
		{



		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
		break;


	case WM_CREATE:
	{
		allShape = new std::vector<Shape*>();
		COLORREF *col = new COLORREF();
		int *currentshape = new int;
		*currentshape = 1;
		*col = RGB(0, 0, 0);
		SetWindowLong(hWnd, 0, (LONG)col);
		SetWindowLong(hWnd, 4, (LONG)allShape);
		SetWindowLong(hWnd, 8, (LONG)currentshape);


		return DefWindowProc(hWnd, message, wParam, lParam);
	}


	case WM_LBUTTONDOWN:
	{
		x1 = x2 = GET_X_LPARAM(lParam);
		y1 = y2 = GET_Y_LPARAM(lParam);
		Shape *t;
		int currentShape = *(int*)GetWindowLong(hWnd, 8);
		
		t = myPool.getShape(currentShape);

		t->setPos(x1, y1, x2, y2);
		
		allShape->push_back(t);
		break;

	}
	case WM_LBUTTONUP:
	{
		x1 = x2 = LOWORD(lParam);
		y1 = y2 = HIWORD(lParam);
		hdc = GetDC(hWnd);
		
		int n = allShape->size();
		COLORREF mcolor = *((COLORREF*)GetWindowLong(hWnd, 0));
		SetROP2(hdc, R2_COPYPEN);
		allShape->at(n - 1)->Draw(hdc, mcolor);
		ReleaseDC(hWnd, hdc);
		break;
	}
	case WM_MOUSEMOVE:
	{
		if (wParam & MK_LBUTTON)
		{
			x2 = GET_X_LPARAM(lParam);
			y2 = GET_Y_LPARAM(lParam);
			
			int currentShape = *(int*)GetWindowLong(hWnd, 8);
			if (currentShape == MY_PIXEL)
			{
				hdc = GetDC(hWnd);
				Shape *t = new mLine();
				SetROP2(hdc, R2_COPYPEN);
				COLORREF mcolor = *((COLORREF*)GetWindowLong(hWnd, 0));
				t->setPos(x1, y1, x2, y2);
				allShape->push_back(t);

				t->Draw(hdc);
				ReleaseDC(hWnd, hdc);
				x1 = x2;
				y1 = y2;
			}
			else
			{
				hdc = GetDC(hWnd);
				SetROP2(hdc, R2_NOTXORPEN);
				COLORREF mcolor = *((COLORREF*)GetWindowLong(hWnd, 0));
				int n = allShape->size();
				allShape->at(n - 1)->Draw(hdc);

				allShape->at(n - 1)->setPos(x1, y1, x2, y2);
				allShape->at(n - 1)->Draw(hdc);
				ReleaseDC(hWnd, hdc);

			}

			//(*v)[n - 1].setPos(x1, y1, x2, y2);
			//InvalidateRect(hWnd, 0, true);
			//UpdateWindow(hWnd);

		}
		break;
	}

	case WM_SIZE:
	{
		UINT w = LOWORD(lParam);
		UINT h = HIWORD(lParam);
		MoveWindow(hWndTextWin, 0, 0, w, h, false);
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	case WM_PAINT:
	{
		hdc = BeginPaint(hWnd, &ps);
		// TODO: Add any drawing code here...
		SelectObject(hdc, GetStockObject(DC_PEN));
		COLORREF mcolor = *((COLORREF*)GetWindowLong(hWnd, 0));
		SetDCPenColor(hdc, mcolor);
		for (int i = 0; i < allShape->size(); ++i)
		{
			(*allShape)[i]->Draw(hdc, mcolor);
		}
		EndPaint(hWnd, &ps);
		break;
	}

	case WM_DESTROY:
	{
		//PostQuitMessage(0);
		for (int i = 0; i < allShape->size(); ++i)
			delete allShape->at(i);
		delete (int*)GetWindowLong(hWnd, 8);
		delete (COLORREF*)GetWindowLong(hWnd, 0);
		delete allShape;

		PostQuitMessage(0);
		break;
	}

	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}