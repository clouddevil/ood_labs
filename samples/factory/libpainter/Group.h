#pragma once
#include "IGroup.h"
#include "CompoundOutlineStyle.h"
#include "CompoundFillStyle.h"

class Group
	: public IGroup
	, private IOutlineStyleProvider
	, private IFillStyleProvider
{
public:
	Group();
	Group(ShapeStorage&& shapes);

	// IGroup
	void Accept(IShapeVisitor& visitor) const override;

	IGroup* GetGroup() override;

	RectD GetFrame() const override;
	void SetFrame(RectD const& rc) override;
		
	uint32_t GetShapeCount() const override;
	IShape& GetShapeAtIndex(uint32_t index) override;
	void InsertShape(IShapeUniquePtr&& shape) override;
	
	IOutlineStyle& GetOutlineStyle() override;
	IOutlineStyle const& GetOutlineStyle() const override;
	
	IFillStyle& GetFillStyle() override;
	IFillStyle const& GetFillStyle() const override;
	
	// IOutlineStyleProvider
	uint32_t GetOutlineStyleCount() const override;
	IOutlineStyle& GetOutlineStyle(uint32_t index) const override;

	// IFillStyleProvider
	uint32_t GetFillStyleCount() const override;
	IFillStyle& GetFillStyle(uint32_t index) const override;

private:
	CompoundFillStyle m_fillStyle;
	CompoundOutlineStyle m_outlineStyle;
	
	ShapeStorage m_shapes;
};

