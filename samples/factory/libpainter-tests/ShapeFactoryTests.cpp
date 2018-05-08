#include "stdafx.h"
#include "../libpainter/Designer.h"
#include "../libpainter/PictureDraft.h"
#include "../libpainter/IShapeFactory.h"

using namespace std;
using boost::algorithm::all_of;
using boost::copy;

class CMockShape : public CShape
{
public:
	CMockShape(const string& descr)
		:descr(descr)
	{
	}
	string descr;
};

struct MockShapeFactory : IShapeFactory
{
	vector<string> shapeDescriptions;
	// Inherited via IShapeFactory
	unique_ptr<CShape> CreateShape(const std::string & description) override
	{
		// «апротоколировали описание созданной фигуры
		shapeDescriptions.push_back(description);
		return make_unique<CMockShape>(description);
	}
};

struct ShapeFactory_
{
	ShapeFactroy factory;	
};

BOOST_FIXTURE_TEST_SUITE(ShapeFactory, ShapeFactory_)
BOOST_AUTO_TEST_SUITE(when_creating_draft)
BOOST_AUTO_TEST_CASE(returns_empty_draft_when_input_is_empty)
{
}

BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()