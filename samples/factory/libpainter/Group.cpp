#include "stdafx.h"
#include "Group.h"
#include "Math.h"

Group::Group()
	: m_fillStyle()
	, m_outlineStyle(m_shapes)
{

}

void Group::Accept(IShapeVisitor& visitor) const
{
	for (auto& s : m_shapes)
	{
		s->Accept(visitor);
	}
}

IGroup* Group::GetGroup()
{
	return this;
}

RectD Group::GetFrame() const
{
	if (m_shapes.empty())
	{
		return {};
	}

	auto& shape = m_shapes.front();
	RectD frame = shape->GetFrame();
	for (auto& s : m_shapes)
	{
		frame.Union(s->GetFrame());
	}
	return frame;
}

void Group::SetFrame(RectD const& groupNewFrame)
{
	auto groupFrame = GetFrame();
	for (auto& s : m_shapes)
	{
		auto frame = s->GetFrame();
		auto newFrame = MoveRect(frame, groupFrame, groupNewFrame);
		s->SetFrame(newFrame);
	}
}

uint32_t Group::GetShapeCount() const
{
	return gsl::narrow_cast<uint32_t>(m_shapes.size());
}

IShape& Group::GetShapeAtIndex(uint32_t index)
{
	return *m_shapes.at(index);
}

void Group::InsertShape(IShapeUniquePtr&& shape)
{
	m_shapes.emplace_back(std::move(shape));
}

IOutlineStyle& Group::GetLineStyle()
{
	return m_outlineStyle;
}

IOutlineStyle const& Group::GetLineStyle() const
{
	return m_outlineStyle;
}

IFillStyle& Group::GetFillStyle()
{
	return m_fillStyle;
}

IFillStyle const& Group::GetFillStyle() const
{
	return m_fillStyle;
}
