#include "stdafx.h"
#include "../libpainter/Designer.h"
#include "../libpainter/PictureDraft.h"
#include "../libpainter/IShapeFactory.h"

using namespace std;
using boost::algorithm::all_of;
using boost::copy;


struct ShapeFactory_
{
	//ShapeFactroy factory;	
};

BOOST_FIXTURE_TEST_SUITE(ShapeFactory, ShapeFactory_)
BOOST_AUTO_TEST_SUITE(when_creating_draft)
BOOST_AUTO_TEST_CASE(returns_empty_draft_when_input_is_empty)
{
}

BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()