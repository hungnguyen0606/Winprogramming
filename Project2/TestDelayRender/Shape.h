#pragma once
#include "stdafx.h"
#include "Resource.h"
#include <algorithm>
#include <utility>

using namespace std;

class Shape
{
protected:
	int x1, x2, y1, y2;
public:
	virtual void setPos(int x1, int y1, int x2, int y2)
	{
		this->x1 = x1;
		this->y1 = y1;
		this->x2 = x2;
		this->y2 = y2;
	}
	virtual void Draw(HDC hdc, COLORREF color =  RGB(0, 0, 0)) = 0;
	Shape();
	virtual ~Shape();
};

class mRectangle :public Shape
{
public:
	void Draw(HDC hdc, COLORREF color)
	{
		
		Rectangle(hdc, min(x1, x2), min(y1, y2), max(x1, x2), max(y1, y2));
	}
};

class mEllipse :public Shape
{
public:
	void Draw(HDC hdc, COLORREF color)
	{
		SetROP2(hdc, R2_COPYPEN);
		Ellipse(hdc, min(x1, x2), min(y1, y2), max(x1, x2), max(y1, y2));
	}
};

class mLine :public Shape
{
public:
	void Draw(HDC hdc, COLORREF color)
	{
		SetROP2(hdc, R2_COPYPEN);
		MoveToEx(hdc, x1, y1, 0);
		LineTo(hdc, x2, y2);
	}
};

class mPixel :public Shape
{
public:
	void Draw(HDC hdc, COLORREF color)
	{
		SetROP2(hdc, R2_COPYPEN);
		
		SetPixel(hdc, x2, y2, color);
	}
};