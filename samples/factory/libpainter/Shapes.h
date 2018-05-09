#pragma once
#include "Shape.h"
#include "Shapes_fwd.h"
#include "CommonTypes.h"

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
	Ellipse(PointD const& pos, PointD const& size)
		: m_pos(pos)
		, m_size(size)
	{
	}

	PointD const& GetPos()  const
	{
		return m_pos;
	}

	PointD const& GetSize() const
	{
		return m_size;
	}

	void Accept(IShapeVisitor& visitor) const
	{
		visitor.Visit(*this);
	};

private:
	PointD m_pos;
	PointD m_size;
};


}
