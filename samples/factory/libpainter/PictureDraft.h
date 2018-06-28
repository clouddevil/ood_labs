#pragma once
#include "IPictureDraft.h"

class PictureDraft
	: public IPictureDraft
{
public:	
	PictureDraft() = default;

	bool IsEmpty()const;

	ShapeIterator begin()const override;
	ShapeIterator end()const override;

	void AddShape(IShapeUniquePtr&& shape);

	IShape& GetShapeAtIndex(uint32_t index);

	PictureDraft(PictureDraft &&) = default;
	PictureDraft& operator=(PictureDraft &&) = default;

	PictureDraft(const PictureDraft &) = delete;
	PictureDraft& operator=(const PictureDraft &) = delete;

	IShapeUniquePtr MoveAsShape();

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
