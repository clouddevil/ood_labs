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
	return stream << "{" << s.fillColor << " }";
}

std::ostream& operator<<(std::ostream& stream, LineStyle const& s)
{
	return stream << "{" << s.fillColor << "," << s.thin << " }";
}


struct Shapes_
{
	IShapeUniquePtr shape = std::make_unique<Group>();

	IShapeUniquePtr r1 = std::make_unique<shape::Rectangle>(RectD{0, 0, 42, 15});
	IShapeUniquePtr t1 = std::make_unique<shape::Triangle>(PointD{0, 0}, PointD{10, 0}, PointD{0, 10});
	IShapeUniquePtr e1 = std::make_unique<shape::Ellipse>(PointD{ 50, 50 }, PointD{ 10, 10 });

	FillStylePtr CreateFillStyle(uint32_t color)
	{
		auto fillStyle = std::make_shared<FillStyle>();
		fillStyle->fillColor = color;
		return fillStyle;
	}

	LineStylePtr CreateLineStyle(uint32_t color, float thin)
	{
		auto outline = std::make_shared<LineStyle>();
		outline->fillColor = color;
		outline->thin = thin;
		return outline;
	}
};

BOOST_FIXTURE_TEST_SUITE(ShapeFactory, Shapes_)
BOOST_AUTO_TEST_SUITE(make_shape)
BOOST_AUTO_TEST_CASE(returns_null_when_group_is_empty)
{
	auto group = shape->GetGroup();
	BOOST_CHECK(!group->GetFillStyle());
	BOOST_CHECK(!group->GetLineStyle());

	RectD rc{ 0 , 0,  0, 0 };
	BOOST_CHECK_EQUAL(group->GetFrame(), rc);
}

BOOST_AUTO_TEST_CASE(returns_style_when_group_contains_one_item)
{
	auto group = shape->GetGroup();
		
	auto fs = CreateFillStyle(0x87654321);	
	auto ls = CreateLineStyle(0x87654321, 10.0f);

	auto& fsRef = *fs;
	auto& lsRef = *ls;

	r1->SetFillStyle(move(fs));
	r1->SetLineStyle(move(ls));

	BOOST_CHECK_NO_THROW(group->InsertShape(move(r1)));

	BOOST_CHECK(group->GetFillStyle());
	BOOST_CHECK(group->GetLineStyle());

	auto gfs = group->GetFillStyle();
	BOOST_CHECK(gfs.get() != &fsRef);
	BOOST_CHECK_EQUAL(*gfs, fsRef);

	auto gls = group->GetLineStyle();
	BOOST_CHECK(gls.get() != &lsRef);
	BOOST_CHECK_EQUAL(*gls, lsRef);

	RectD rc{ 0 , 0,  42, 15 };
	BOOST_CHECK_EQUAL(group->GetFrame(), rc);
}

BOOST_AUTO_TEST_CASE(returns_style_when_group_contains_more_then_one_item)
{
	auto group = shape->GetGroup();

	auto color = 0x87654321;

	r1->SetFillStyle(CreateFillStyle(color));
	r1->SetLineStyle(CreateLineStyle(color, 10.0f));

	t1->SetFillStyle(CreateFillStyle(color));
	t1->SetLineStyle(CreateLineStyle(color, 10.0f));

	BOOST_CHECK_NO_THROW(group->InsertShape(move(r1)));
	BOOST_CHECK_NO_THROW(group->InsertShape(move(t1)));

	BOOST_CHECK(group->GetFillStyle());
	BOOST_CHECK(group->GetLineStyle());

	auto gfs = group->GetFillStyle();
	BOOST_CHECK_EQUAL(gfs->fillColor, color);

	auto lfs = group->GetLineStyle();
	BOOST_CHECK_EQUAL(lfs->fillColor, color);
	
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