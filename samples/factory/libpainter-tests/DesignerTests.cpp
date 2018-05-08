#include "stdafx.h"
#include "../libpainter/Designer.h"
#include "../libpainter/PictureDraft.h"
#include "../libpainter/IShapeFactory.h"
#include "Mocks.h"


using namespace std;
using boost::algorithm::all_of;
using boost::copy;

struct Designer_
{
	MockShapeFactory factory;
	Designer designer = Designer(factory);
};

BOOST_FIXTURE_TEST_SUITE(DesignerTestSuite, Designer_)
	BOOST_AUTO_TEST_SUITE(when_creating_draft)
		BOOST_AUTO_TEST_CASE(returns_empty_draft_when_input_is_empty)
		{
			istringstream input;
			auto draft = designer.CreateDraft(input);
			BOOST_CHECK(draft.IsEmpty());
			BOOST_CHECK(input.eof());
		}

		struct when_creating_draft_with_non_empty_input_ : Designer_
		{
			vector<string> expectedShapeDescriptions = {
				"square", "circle", "triangle"
			};
			stringstream strm;
			PictureDraft returnedDraft;
			when_creating_draft_with_non_empty_input_()
			{
				copy(expectedShapeDescriptions, ostream_iterator<string>(strm, "\n"));
				returnedDraft = designer.CreateDraft(strm);
			}
		};
		BOOST_FIXTURE_TEST_SUITE(when_creating_draft_with_non_empty_input, when_creating_draft_with_non_empty_input_)
			BOOST_AUTO_TEST_CASE(passes_each_line_from_input_to_shape_factory)
			{
				BOOST_CHECK(factory.shapeDescriptions == expectedShapeDescriptions);
			}
			BOOST_AUTO_TEST_CASE(returns_draft_with_shapes_created_by_factory)
			{
				vector<string> shapeDescriptions;
				std::transform(returnedDraft.begin(), returnedDraft.end(), back_inserter(shapeDescriptions), [](auto & shape) {
					auto shapeAsMockShape = dynamic_cast<const MockShape*>(&shape);
					BOOST_REQUIRE(shapeAsMockShape);
					return shapeAsMockShape->descr;
				});
				BOOST_CHECK(shapeDescriptions == expectedShapeDescriptions);
			}
		BOOST_AUTO_TEST_SUITE_END()
	BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()