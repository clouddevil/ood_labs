#pragma once
#include "IShape.h"

class Shape
	: public IShape
{
public:
	void Accept(IShapeVisitor& visitor) override;

	IGroup* GetGroup() override;

	Rect GetFrame()const override;
	void SetFrame(Rect const& rc) override;

	LineStylePtr GetLineStyle()const override;
	void SetLineStyle(LineStylePtr const& style) override;

	FillStylePtr GetFillStyle()const override;
	void SetFillStyle(FillStylePtr const& style) override;

private:
	Rect m_frame;
	FillStylePtr m_fill;
	LineStylePtr m_line;
};

