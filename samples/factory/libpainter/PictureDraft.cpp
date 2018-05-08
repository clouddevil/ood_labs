#include "stdafx.h"
#include "PictureDraft.h"

bool PictureDraft::IsEmpty() const
{
	return m_shapes.empty();
}

PictureDraft::ConstIterator PictureDraft::begin() const
{
	return m_shapes.begin();
}

PictureDraft::ConstIterator PictureDraft::end() const
{
	return m_shapes.end();
}

void PictureDraft::AddShape(IShapeUniquePtr&& shape)
{
	m_shapes.push_back(move(shape));
}



