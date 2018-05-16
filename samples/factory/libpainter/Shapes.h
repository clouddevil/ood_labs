#pragma once
#include "Shape.h"
#include "Shapes_fwd.h"
#include "CommonTypes.h"
#include "Math.h"

namespace shape
{

class Rectangle final
	: public Shape
{
public:
	Rectangle(RectD rc)
		: m_rect(rc)
	{
	}

	RectD GetFrame() const override
	{
		return m_rect;
	}

	void SetFrame(RectD const& rc) override
	{
		m_rect = rc;
	}

	RectD const& GetRect() const
	{
		return m_rect;
	}

	void Accept(IShapeVisitor& visitor) const 
	{
		visitor.Visit(*this);
	};

private:
	RectD m_rect;
};

class Triangle final
	: public Shape
{
public:
	Triangle(PointD const& v1, PointD const& v2, PointD const& v3)
		: m_vtx1(v1)
		, m_vtx2(v2)
		, m_vtx3(v3)
	{
	}

	RectD GetFrame() const override
	{
		return CalcuateBounds({m_vtx1, m_vtx2, m_vtx3});
	}

	void SetFrame(RectD const& newFrame) override
	{
		auto frame = GetFrame();
		m_vtx1 = MovePoint(m_vtx1, frame, newFrame);
		m_vtx2 = MovePoint(m_vtx2, frame, newFrame);
		m_vtx3 = MovePoint(m_vtx3, frame, newFrame);
	}

	PointD const& GetVertex1()  const
	{
		return m_vtx1;
	}

	PointD const& GetVertex2() const
	{
		return m_vtx2;
	}

	PointD const& GetVertex3() const
	{
		return m_vtx3;
	}

	void Accept(IShapeVisitor& visitor) const
	{
		visitor.Visit(*this);
	};

private: 
	PointD m_vtx1;
	PointD m_vtx2;
	PointD m_vtx3;
};

class Ellipse final
	: public Shape
{
public:
	Ellipse(PointD const& center, PointD const& radius)
		: m_center(center)
		, m_radius(radius)
	{
	}

	RectD GetFrame() const override
	{
		RectD frame;
		frame.left = m_center.x - m_radius.x;
		frame.top = m_center.y - m_radius.y;
		frame.width = 2 * m_radius.x;
		frame.height = 2 * m_radius.y;
		return frame;
	}

	void SetFrame(RectD const& newFrame) override
	{
		m_radius = { newFrame.width / 2, newFrame.height / 2 };
		m_center = { newFrame.left + m_radius.x, newFrame.top + m_radius.y };		
	}

	PointD const& GetCenter()  const
	{
		return m_center;
	}

	PointD const& GetSize() const
	{
		return m_radius;
	}

	void Accept(IShapeVisitor& visitor) const
	{
		visitor.Visit(*this);
	};

private:
	PointD m_center;
	PointD m_radius;
};


}
