#pragma once
#include "IShape.h"

class Shape
	: public IShape
{
public:
	void Accept(IShapeVisitor& visitor) const override;

	IGroup* GetGroup() override;

	RectD GetFrame()const override;
	void SetFrame(RectD const& rc) override;

	LineStylePtr GetLineStyle()const override;
	void SetLineStyle(LineStylePtr const& style) override;

	FillStylePtr GetFillStyle()const override;
	void SetFillStyle(FillStylePtr const& style) override;

private:
	RectD m_frame;
	FillStylePtr m_fill;
	LineStylePtr m_line;
};

