#include "stdafx.h"
#include "Shape.h"

template <typename T>
T Clone(T const& t)
{
	return t ? t->Clone() : nullptr;
}

void Shape::Accept(IShapeVisitor& /*visitor*/) const
{
	throw std::logic_error("The method or operation is not implemented.");
}

IGroup* Shape::GetGroup()
{
	return nullptr;
}

LineStylePtr Shape::GetLineStyle()const
{
	return Clone(m_line);
}

void Shape::SetLineStyle(LineStylePtr const& style)
{
	m_line = Clone(style);
}

FillStylePtr Shape::GetFillStyle()const
{
	return Clone(m_fill);
}

void Shape::SetFillStyle(FillStylePtr const& style)
{
	m_fill = Clone(style);
}
