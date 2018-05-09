#include "stdafx.h"
#include "Shape.h"

void Shape::Accept(IShapeVisitor& /*visitor*/) const
{
	throw std::logic_error("The method or operation is not implemented.");
}

IGroup* Shape::GetGroup()
{
	return nullptr;
}

RectD Shape::GetFrame()const
{
	return m_frame;
}

void Shape::SetFrame(RectD const& rc)
{
	m_frame = rc;
}

LineStylePtr Shape::GetLineStyle()const
{
	return m_line;
}

void Shape::SetLineStyle(LineStylePtr const& style)
{
	m_line = style;
}

FillStylePtr Shape::GetFillStyle()const
{
	return m_fill;
}

void Shape::SetFillStyle(FillStylePtr const& style)
{
	m_fill = style;
}
