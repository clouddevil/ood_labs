#include "stdafx.h"

#include "../libpainter/ShapeFactroy.h"

using namespace std;
using boost::algorithm::all_of;
using boost::copy;


struct ShapeFactory_
{
	ShapeFactroy factory;	
};

BOOST_FIXTURE_TEST_SUITE(ShapeFactory, ShapeFactory_)
BOOST_AUTO_TEST_SUITE(creating_shape)
BOOST_AUTO_TEST_CASE(returns_empty_shape_when_input_is_empty)
{
	BOOST_CHECK(!factory.CreateShape(""));
}

BOOST_AUTO_TEST_CASE(throws_on_incorrect_input)
{
	BOOST_CHECK_THROW(factory.CreateShape("test rect "), std::runtime_error);
}

BOOST_AUTO_TEST_CASE(shape_on_correct_input)
{
	BOOST_CHECK(factory.CreateShape("rect 180 460 400 80 0xFF0000 -  "));
}

BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()