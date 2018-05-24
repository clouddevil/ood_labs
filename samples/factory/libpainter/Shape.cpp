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

IOutlineStyle& Shape::GetOutlineStyle()
{
	return m_lineStyle;
}

IOutlineStyle const& Shape::GetOutlineStyle() const
{
	return m_lineStyle;
}

IFillStyle& Shape::GetFillStyle()
{
	return m_fillStyle;
}

IFillStyle const& Shape::GetFillStyle() const
{
	return m_fillStyle;
}

