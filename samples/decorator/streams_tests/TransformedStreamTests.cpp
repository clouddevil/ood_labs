#include "stdafx.h"
#include "..\streams\FileInputStream.h"
#include "..\streams\MemoryInputStream.h"
#include "StreamTestFunctions.h"
#include "..\streams\TransformedInputStream.h"
#include "..\streams\CaesarCipherTransform.h"

namespace
{

class StreamDataTransform
	: public IStreamDataTransform
{
public:
	uint8_t Transform(uint8_t byte) override
	{
		return byte;
	}	
};


struct StreamFixture
	: BaseFixture
{
};

}

BOOST_FIXTURE_TEST_SUITE(TransformedStreamTestSuite, StreamFixture)

BOOST_AUTO_TEST_CASE(TestTransformedOutputStreams)
{
	auto is = std::make_shared<MemoryInputStream>();
	is->SetData(vec(digits));

	auto ts = std::make_shared<StreamDataTransform>();

	TransformedInputStream s(is, ts);
	CheckOnDigits(s);
}

BOOST_AUTO_TEST_CASE(TestTransformedCeasarInputStreams)
{	
	auto ts1 = std::make_shared<CaesarCipherTransform>(true);
	auto ts2 = std::make_shared<CaesarCipherTransform>(false);

	std::vector<uint8_t> values = { '0', 4, 255, 36 };
	for (auto& v : values)
	{
		BOOST_CHECK_EQUAL(ts1->Transform(ts2->Transform(v)), v);
	}
}

BOOST_AUTO_TEST_SUITE_END()
