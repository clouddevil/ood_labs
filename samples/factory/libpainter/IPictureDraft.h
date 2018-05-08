#pragma once
#include "IShape.h"

class IPictureDraft
{
public:
	using ShapeStorage = std::vector<IShapeUniquePtr>;
	using ConstIterator = boost::indirect_iterator<ShapeStorage::const_iterator, const IShape&>;

	virtual ConstIterator begin()const = 0;
	virtual ConstIterator end()const = 0;

	virtual ~IPictureDraft() = default;
};

