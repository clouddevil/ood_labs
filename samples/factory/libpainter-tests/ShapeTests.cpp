#include "stdafx.h"
#include "../libpainter/Shape.h"
#include "../libpainter/ShapeFactroy.h"
#include "../libpainter/Group.h"
#include "../libpainter/Shapes.h"


std::ostream& operator<<(std::ostream& stream, RectD const& rc)
{
	return stream << "{" << rc.left << "," << rc.top << "," << rc.width << "," << rc.height << " }";
}


std::ostream& operator<<(std::ostream& stream, FillStyle const& s)
{
	return stream << "{" << s.GetColor() << " }";
}

std::ostream& operator<<(std::ostream& stream, OutlineStyle const& s)
{
	return stream << "{" << s.GetColor() << "," << s.GetThickness() << " }";
}


struct Shapes_
{
	IShapeUniquePtr shape = std::make_unique<Group>();

	IShapeUniquePtr r1 = std::make_unique<shape::Rectangle>(RectD{0, 0, 42, 15});
	IShapeUniquePtr t1 = std::make_unique<shape::Triangle>(PointD{0, 0}, PointD{10, 0}, PointD{0, 10});
	IShapeUniquePtr e1 = std::make_unique<shape::Ellipse>(PointD{ 50, 50 }, PointD{ 10, 10 });

	FillStyle CreateFillStyle(uint32_t color)
	{
		FillStyle s;
		s.SetColor(color);		
		return s;
	}

	OutlineStyle CreateLineStyle(uint32_t color, float thin)
	{
		OutlineStyle s;
		s.SetColor(color);
		s.SetThickness(thin);
		return s;
// 		auto outline = std::make_shared<LineStyle>();
// 		outline->fillColor = color;
// 		outline->thin = thin;
// 		return outline;
	}
};

BOOST_FIXTURE_TEST_SUITE(ShapeFactory, Shapes_)
BOOST_AUTO_TEST_SUITE(make_shape)
BOOST_AUTO_TEST_CASE(returns_null_when_group_is_empty)
{
	auto group = shape->GetGroup();
	BOOST_CHECK_NO_THROW(group->GetFillStyle());
	BOOST_CHECK_NO_THROW(group->GetOutlineStyle());

	RectD rc{ 0 , 0,  0, 0 };
	BOOST_CHECK_EQUAL(group->GetFrame(), rc);
}

BOOST_AUTO_TEST_CASE(returns_style_when_group_contains_one_item)
{
	auto group = shape->GetGroup();
	
	auto& gfs = group->GetFillStyle();
	auto& gls = group->GetOutlineStyle();

	BOOST_CHECK_NO_THROW(group->InsertShape(move(r1)));

	auto& gfs1 = group->GetFillStyle();
	auto& gls1 = group->GetOutlineStyle();
	
	BOOST_CHECK_EQUAL(&gfs, &gfs1);
	BOOST_CHECK_EQUAL(&gls, &gls1);

	RectD rc{ 0 , 0,  42, 15 };
	BOOST_CHECK_EQUAL(group->GetFrame(), rc);
}

BOOST_AUTO_TEST_CASE(returns_style_when_group_contains_more_then_one_item)
{
	auto group = shape->GetGroup();

	auto color = 0x87654321;

	r1->GetFillStyle().SetColor(color);
	r1->GetOutlineStyle().SetColor(color);
	r1->GetOutlineStyle().SetThickness(10.0f);

	t1->GetFillStyle().SetColor(color);
	t1->GetOutlineStyle().SetColor(color);
	t1->GetOutlineStyle().SetThickness(10.0f);

	auto& gfs = group->GetFillStyle();
	auto& gls = group->GetOutlineStyle();

	BOOST_CHECK_NO_THROW(group->InsertShape(move(r1)));
	BOOST_CHECK_NO_THROW(group->InsertShape(move(t1)));

	auto& gfs1 = group->GetFillStyle();
	auto& gls1 = group->GetOutlineStyle();

	BOOST_CHECK_EQUAL(&gfs, &gfs1);
	BOOST_CHECK_EQUAL(&gls, &gls1);
		
	BOOST_CHECK_EQUAL(gfs.GetColor(), color);	
	BOOST_CHECK_EQUAL(gls.GetColor(), color);
	
	RectD rc{ 0 , 0,  42, 15 };
	BOOST_CHECK_EQUAL(group->GetFrame(), rc);
}

BOOST_AUTO_TEST_CASE(returns_frame_when_group_contains_more_then_one_item)
{
	auto group = shape->GetGroup();

	auto& r1Ref = *r1;
	auto& t1Ref = *t1;
	auto& e1Ref = *e1;

	BOOST_CHECK_NO_THROW(group->InsertShape(move(r1)));
	BOOST_CHECK_NO_THROW(group->InsertShape(move(t1)));
	BOOST_CHECK_NO_THROW(group->InsertShape(move(e1)));
	
	RectD rc{ 0 , 0,  60, 60 };
	BOOST_CHECK_EQUAL(group->GetFrame(), rc);

	BOOST_CHECK_NO_THROW(group->SetFrame({ 50, 50, 120, 120 }));
	
	BOOST_CHECK_EQUAL(r1Ref.GetFrame(), RectD(50, 50, 84, 30));
	BOOST_CHECK_EQUAL(t1Ref.GetFrame(), RectD(50, 50, 20, 20));
	BOOST_CHECK_EQUAL(e1Ref.GetFrame(), RectD(130, 130, 40, 40));

	BOOST_CHECK_EQUAL(group->GetFrame(), RectD( 50, 50, 120, 120 ));
}


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()