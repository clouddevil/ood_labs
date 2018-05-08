#pragma once
#include "IPictureDraft.h"

class CPictureDraft
	: public IPictureDraft
{

public:	
	CPictureDraft();

	bool IsEmpty()const;

	ConstIterator begin()const;
	ConstIterator end()const;

	void AddShape(IShapeUniquePtr&& shape);

	CPictureDraft(CPictureDraft &&) = default;
	CPictureDraft& operator=(CPictureDraft &&) = default;

	CPictureDraft(const CPictureDraft &) = delete;
	CPictureDraft& operator=(const CPictureDraft &) = delete;

private:
	ShapeStorage m_shapes;
};

inline CPictureDraft::ConstIterator begin(const CPictureDraft & draft)
{
	return draft.begin();
}

inline CPictureDraft::ConstIterator end(const CPictureDraft & draft)
{
	return draft.end();
}
