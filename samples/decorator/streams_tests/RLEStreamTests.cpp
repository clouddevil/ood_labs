#include "stdafx.h"
#include "..\streams\RLEInputStream.h"
#include "StreamTestFunctions.h"

namespace
{

struct RLEStreamFixture
	: BaseFixture
{
	vec data{
		9, 1, 
		4, 3,
		6, 1,
		0, 2,
		7, 1
		};

	IInputDataStreamUniquePtr Construct()
	{
		auto buffer = std::make_unique<MemoryInputStream>();
		BOOST_CHECK_NO_THROW(buffer->SetData(vec(data)));

		return std::make_unique<RLEInputStream>(std::move(buffer));
	}
};


}

BOOST_FIXTURE_TEST_SUITE(RLEStreamTestSuite, RLEStreamFixture)

BOOST_AUTO_TEST_CASE(TestRLEInputStreamReadBlock)
{	
	auto s = Construct();

	vec iData(10, 42);
	BOOST_CHECK_NO_THROW(s->ReadBlock(iData.data(), iData.size()));
	BOOST_CHECK(s->IsEOF());
	BOOST_CHECK_EQUAL(iData, vec({ 9, 4, 4, 4, 6, 0, 0, 7, 42, 42 }));
}

BOOST_AUTO_TEST_CASE(TestRLEInputStreamReadByte)
{
	auto s = Construct();

	BOOST_CHECK_EQUAL(s->ReadByte(), 9);
	BOOST_CHECK_EQUAL(s->ReadByte(), 4);
	BOOST_CHECK_EQUAL(s->ReadByte(), 4);
	BOOST_CHECK_EQUAL(s->ReadByte(), 4);
	BOOST_CHECK_EQUAL(s->ReadByte(), 6);
	BOOST_CHECK_EQUAL(s->ReadByte(), 0);
	BOOST_CHECK(!s->IsEOF());	
}

BOOST_AUTO_TEST_SUITE_END()
