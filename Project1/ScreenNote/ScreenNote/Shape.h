#pragma once
#include "stdafx.h"
#include "Resource.h"
#include <algorithm>
#include <utility>
#include <vector>
using namespace std;

#define MY_RECTANGLE 0
#define MY_LINE 2
#define MY_ELLIPSE 1
#define MY_PIXEL 3

class Shape;
class mRectangle;
class mEllipse;
class mLine;



class Shape
{
protected:
	int x1, x2, y1, y2;
public:
	int mytype;
	virtual void setPos(int x1, int y1, int x2, int y2)
	{
		this->x1 = x1;
		this->y1 = y1;
		this->x2 = x2;
		this->y2 = y2;
	}
	virtual void Draw(HDC hdc, COLORREF color =  RGB(0, 0, 0)) = 0;
	virtual Shape* Clone() = 0;
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

	Shape* Clone()
	{
		Shape* res = new mRectangle();
		res->mytype = 0;
		res->setPos(this->x1, this->y1, this->x2, this->y2);
		return res;
	}
};

class mEllipse :public Shape
{
public:
	void Draw(HDC hdc, COLORREF color)
	{
		//SetROP2(hdc, R2_COPYPEN);
		Ellipse(hdc, min(x1, x2), min(y1, y2), max(x1, x2), max(y1, y2));
	}
	Shape* Clone()
	{
		Shape* res = new mEllipse();
		res->mytype = 1;
		res->setPos(this->x1, this->y1, this->x2, this->y2);
		return res;
	}
};

class mLine :public Shape
{
public:
	void Draw(HDC hdc, COLORREF color)
	{
		//SetROP2(hdc, R2_COPYPEN);
		MoveToEx(hdc, x1, y1, 0);
		LineTo(hdc, x2, y2);
	}
	Shape* Clone()
	{
		Shape* res = new mLine();
		res->mytype = 2;
		res->setPos(this->x1, this->y1, this->x2, this->y2);
		return res;
	}
};

class mPixel :public Shape
{
public:
	void Draw(HDC hdc, COLORREF color)
	{
		MoveToEx(hdc, x1, y1, 0);
		LineTo(hdc, x2, y2);
	}
	Shape* Clone()
	{
		Shape* res = new mPixel;
		res->mytype = 3;
		res->setPos(this->x1, this->y1, this->x2, this->y2);
		return res;
	}
};

class PoolShape
{
protected:
	vector<Shape*> pool;

public:
	void addShape(Shape* sh)
	{
		pool.push_back(sh->Clone());
	}

	//Get a shape of this TYPE
	//You have to delete it yourself
	Shape* getShape(int TYPE)
	{
		if (TYPE < 0 || TYPE >= pool.size())
			return NULL;
		return pool[TYPE]->Clone();
	}

	PoolShape()
	{
	
		pool.push_back(new mRectangle());
		pool.push_back(new mEllipse());
		pool.push_back(new mLine);
		pool.push_back(new mPixel);
	}

	~PoolShape()
	{
		for (int i = 0; i < pool.size(); ++i)
			delete pool[i];
	}

};