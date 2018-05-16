#pragma once
#include "IShape.h"
#include "ShapeStorage.h"


class IGroup
	: public IShape
{
public:
	virtual uint32_t GetShapeCount() const = 0;
	virtual IShape& GetShapeAtIndex(uint32_t index) = 0;
	virtual void InsertShape(IShapeUniquePtr&& shape) = 0;

	virtual ~IGroup() = default;
};

