#include "stdafx.h"
#include "..\streams\FileInputStream.h"
#include "..\streams\MemoryInputStream.h"
#include "StreamTestFunctions.h"
#include "..\streams\TransformedInputDataStream.h"
#include "..\streams\CaesarCipherTransform.h"

namespace
{

struct StreamFixture
{
};

}

BOOST_FIXTURE_TEST_SUITE(TransformedStreamTestSuite, StreamFixture)

BOOST_AUTO_TEST_CASE(TestTransformedOutputStreams)
{
	auto is = std::make_unique<MemoryInputStream>("0123456789");
	auto ts = std::make_unique<StreamDataTransform>();

	TransformedInputDataStream s(std::move(is), std::move(ts));
	CheckOnDigits(s);
}

BOOST_AUTO_TEST_CASE(TestTransformedCeasarInputStreams)
{	
	auto ts1 = std::make_unique<CaesarCipherTransform>(true);
	auto ts2 = std::make_unique<CaesarCipherTransform>(false);

	std::vector<uint8_t> values = { '0', 4, 255, 36 };
	for (auto& v : values)
	{
		BOOST_CHECK_EQUAL(ts1->Transform(ts2->Transform(v)), v);
	}
}

BOOST_AUTO_TEST_SUITE_END()
