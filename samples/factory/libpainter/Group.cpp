#include "stdafx.h"
#include "Group.h"
#include "Math.h"

Group::Group()
	: m_fillStyle(*this)
	, m_outlineStyle(*this)
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

IOutlineStyle& Group::GetOutlineStyle()
{
	return m_outlineStyle;
}

IOutlineStyle const& Group::GetOutlineStyle() const
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

IFillStyle& Group::GetFillStyle(uint32_t index) const
{
	auto const& s = m_shapes.at(index);
	return s->GetFillStyle();
}

uint32_t Group::GetOutlineStyleCount() const
{
	return static_cast<uint32_t>(m_shapes.size());
}

IOutlineStyle& Group::GetOutlineStyle(uint32_t index) const
{
	auto const& s = m_shapes.at(index);
	return s->GetOutlineStyle();
}

uint32_t Group::GetFillStyleCount() const
{
	return static_cast<uint32_t>(m_shapes.size());
}

