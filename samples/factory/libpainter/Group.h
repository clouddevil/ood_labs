#pragma once
#include "IGroup.h"
#include "CompoundOutlineStyle.h"
#include "CompoundFillStyle.h"

class Group
	: public IGroup
{
public:
	Group();

	void Accept(IShapeVisitor& visitor) const override;

	IGroup* GetGroup() override;

	RectD GetFrame() const override;
	void SetFrame(RectD const& rc) override;
		
	uint32_t GetShapeCount() const override;
	IShape& GetShapeAtIndex(uint32_t index) override;
	void InsertShape(IShapeUniquePtr&& shape) override;
	
	IOutlineStyle& GetLineStyle() override;
	IOutlineStyle const& GetLineStyle() const override;
	
	IFillStyle& GetFillStyle() override;
	IFillStyle const& GetFillStyle() const override;

private:
	CompoundFillStyle m_fillStyle;
	CompoundOutlineStyle m_outlineStyle;
	
	ShapeStorage m_shapes;
};

