#include "stdafx.h"
#include "Group.h"
#include "Math.h"

namespace
{

template <class T, class U>
bool SharedObjectEquals(const std::shared_ptr<T>& a, const std::shared_ptr<U>& b)
{
	if (a == b)
	{
		return true;
	}
	if (a && b)
	{
		return *a == *b;
	}
	return false;
}

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

LineStylePtr Group::GetLineStyle() const
{
	if (!m_shapes.empty())
	{
		auto& shape = m_shapes.front();
		auto style = shape->GetLineStyle();

		bool equal = std::all_of(m_shapes.begin() + 1, m_shapes.end(), [&](auto const& s) {
			return SharedObjectEquals(s->GetLineStyle(), style);
		});

		if (equal && style)
		{
			return style->Clone();
		}
	}
	return nullptr;
}

void Group::SetLineStyle(LineStylePtr const& style)
{
	for (auto& s : m_shapes)
	{
		s->SetLineStyle(style);
	}
}

FillStylePtr Group::GetFillStyle() const
{
	if (!m_shapes.empty())
	{
		auto& shape = m_shapes.front();
		auto style = shape->GetFillStyle();

		bool equal = std::all_of(m_shapes.begin() + 1, m_shapes.end(), [&](auto const& s) {
			return SharedObjectEquals(s->GetFillStyle(), style);
		});

		if (equal && style)
		{
			return style->Clone();
		}
	}
	return nullptr;
}

void Group::SetFillStyle(FillStylePtr const& style)
{
	for (auto& s : m_shapes)
	{
		s->SetFillStyle(style);
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
