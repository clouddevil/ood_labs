#include "stdafx.h"
#include "PictureDraft.h"

bool PictureDraft::IsEmpty() const
{
	return m_shapes.empty();
}

ShapeIterator PictureDraft::begin() const
{
	return m_shapes.begin();
}

ShapeIterator PictureDraft::end() const
{
	return m_shapes.end();
}

void PictureDraft::AddShape(IShapeUniquePtr&& shape)
{
	if (shape)
	{
		m_shapes.emplace_back(move(shape));
	}
}

IShape& PictureDraft::GetShapeAtIndex(uint32_t index)
{
	return *m_shapes.at(index);
}


