#include "stdafx.h"
#include "Group.h"


void Group::Accept(IShapeVisitor& /*visitor*/) const
{
	throw std::logic_error("The method or operation is not implemented.");
}

IGroup* Group::GetGroup()
{
	throw std::logic_error("The method or operation is not implemented.");
}

RectD Group::GetFrame() const
{
	throw std::logic_error("The method or operation is not implemented.");
}

void Group::SetFrame(RectD const& /*rc*/)
{
	throw std::logic_error("The method or operation is not implemented.");
}

LineStylePtr Group::GetLineStyle() const
{
	throw std::logic_error("The method or operation is not implemented.");
}

void Group::SetLineStyle(LineStylePtr const& /*style*/)
{
	throw std::logic_error("The method or operation is not implemented.");
}

FillStylePtr Group::GetFillStyle() const
{
	throw std::logic_error("The method or operation is not implemented.");
}

void Group::SetFillStyle(FillStylePtr const& /*style*/)
{
	throw std::logic_error("The method or operation is not implemented.");
}
