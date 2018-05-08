#pragma once
#include "IPictureDraft.h"

class PictureDraft
	: public IPictureDraft
{
public:	
	PictureDraft() = default;

	bool IsEmpty()const;

	ConstIterator begin()const;
	ConstIterator end()const;

	void AddShape(IShapeUniquePtr&& shape);

	PictureDraft(PictureDraft &&) = default;
	PictureDraft& operator=(PictureDraft &&) = default;

	PictureDraft(const PictureDraft &) = delete;
	PictureDraft& operator=(const PictureDraft &) = delete;

private:
	ShapeStorage m_shapes;
};

inline PictureDraft::ConstIterator begin(const PictureDraft & draft)
{
	return draft.begin();
}

inline PictureDraft::ConstIterator end(const PictureDraft & draft)
{
	return draft.end();
}
