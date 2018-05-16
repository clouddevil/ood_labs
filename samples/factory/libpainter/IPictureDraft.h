#pragma once
#include "IShape.h"
#include "ShapeStorage.h"

class IPictureDraft
{
public:
	virtual ShapeIterator begin()const = 0;
	virtual ShapeIterator end()const = 0;

	virtual ~IPictureDraft() = default;
};

