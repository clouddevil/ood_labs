#pragma once
#include "IGroup.h"


class Group
	: public IGroup
{
public:
	virtual void Accept(IShapeVisitor& visitor) const override;

	virtual IGroup* GetGroup() override;

	virtual RectD GetFrame() const override;
	virtual void SetFrame(RectD const& rc) override;

	LineStylePtr GetLineStyle() const override;
	void SetLineStyle(LineStylePtr const& style) override;
	
	FillStylePtr GetFillStyle() const override;
	void SetFillStyle(FillStylePtr const& style) override;

	uint32_t GetShapeCount() const override;
	IShape& GetShapeAtIndex(uint32_t index) override;
	void InsertShape(IShapeUniquePtr&& shape) override;
	
private:
	ShapeStorage m_shapes;
};

