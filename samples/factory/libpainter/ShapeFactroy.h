#pragma once
#include "IShapeFactory.h"

class ShapeFactroy
	: public IShapeFactory
{
public:	
	std::unique_ptr<CShape> CreateShape(const std::string & description) override;
};


