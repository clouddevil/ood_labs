#pragma once
#include "Shape.h"
#include "Shapes_fwd.h"

namespace shape
{

class Rectangle final
	: public Shape
{
public:
	void Accept(IShapeVisitor& visitor) const 
	{
		visitor.Visit(*this);
	};
};

class Triangle final
	: public Shape
{
public:
	void Accept(IShapeVisitor& visitor) const
	{
		visitor.Visit(*this);
	};
};


class Ellipse final
	: public Shape
{
public:
	void Accept(IShapeVisitor& visitor) const
	{
		visitor.Visit(*this);
	};
};


}
