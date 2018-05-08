#pragma once
#include "IShape.h"

class IShapeFactory
{
public:
	virtual IShapeUniquePtr CreateShape(const std::string & description) = 0;

	virtual ~IShapeFactory() = default;
};