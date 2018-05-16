#pragma once

using ShapeStorage = std::vector<IShapeUniquePtr>;
using ShapeIterator = boost::indirect_iterator<ShapeStorage::const_iterator, const IShape&>;