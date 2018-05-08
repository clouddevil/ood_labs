#pragma once
#include "IShapeFactory.h"

class ShapeFactroy
	: public IShapeFactory
{
public:	
	IShapeUniquePtr CreateShape(const std::string & description) override;
};


