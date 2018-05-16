#pragma once
#include "IPictureDraft.h"

class PictureDraft
	: public IPictureDraft
{
public:	
	PictureDraft() = default;

	bool IsEmpty()const;

	ShapeIterator begin()const;
	ShapeIterator end()const;

	void AddShape(IShapeUniquePtr&& shape);

	PictureDraft(PictureDraft &&) = default;
	PictureDraft& operator=(PictureDraft &&) = default;

	PictureDraft(const PictureDraft &) = delete;
	PictureDraft& operator=(const PictureDraft &) = delete;

private:
	ShapeStorage m_shapes;
};

inline ShapeIterator begin(const PictureDraft & draft)
{
	return draft.begin();
}

inline ShapeIterator end(const PictureDraft & draft)
{
	return draft.end();
}
