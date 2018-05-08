#pragma once
#include "Point.h"
#include "Color.h"

class ICanvas
{
public:
	virtual void SetColor(Color color) = 0;
	virtual void DrawLine(Point const& form, Point const& to) = 0;
	virtual void DrawEllipse(Point const& l, Point const& t, Point const& w, Point const& h) = 0;
};

