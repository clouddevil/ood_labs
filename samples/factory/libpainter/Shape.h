#pragma once
#include "FillStyle.h"
#include "OutlineStyle.h"
#include "IShape.h"

class Shape
	: public IShape
{
public:
	void Accept(IShapeVisitor& visitor) const override;

	IGroup* GetGroup() override;

	IOutlineStyle& GetLineStyle() override;
	IOutlineStyle const& GetLineStyle() const override;
	
	IFillStyle& GetFillStyle() override;
	IFillStyle const& GetFillStyle() const override;

private:
	FillStyle m_fillStyle;
	OutlineStyle m_lineStyle;
};

