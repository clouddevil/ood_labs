#pragma once
#include "Shapes_fwd.h"

class IShapeVisitor
{
public:
	virtual ~IShapeVisitor() = default;

	virtual void Visit(shape::Rectangle const& shape) = 0;
	virtual void Visit(shape::Triangle const& shape) = 0;
	virtual void Visit(shape::Ellipse const& shape) = 0;
};

