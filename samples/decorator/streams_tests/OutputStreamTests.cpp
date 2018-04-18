#include "stdafx.h"
#include "..\streams\FileOutputStream.h"
#include "..\streams\MemoryOutputStream.h"
#include "..\streams\FileInputStream.h"
#include "StreamTestFunctions.h"
#include "TempFileName.h"

namespace
{

struct OutputStreamFixture
	: BaseFixture
{	
	
};


}

BOOST_FIXTURE_TEST_SUITE(OutputStreamTestSuite, OutputStreamFixture)

BOOST_AUTO_TEST_CASE(TestOnEmpty)
{
	TempFilename fn("test_empty.txt");

	{
		FileOutputStream s(fn.name());	
	}

	FileInputStream empty(fn.name());	
	CheckOnEmptyData(empty);
}

BOOST_AUTO_TEST_CASE(TestOnDigits)
{
	TempFilename fn("test_digits.txt");
		
	{
		FileOutputStream s(fn.name());
		BOOST_CHECK_NO_THROW(s.WriteByte('0'));
		BOOST_CHECK_NO_THROW(s.WriteByte('1'));

		std::vector<uint8_t> block{ '2', '3', '4', '5', '6', '7', '8', '9' };
		BOOST_CHECK_NO_THROW(s.WriteBlock(block.data(), block.size()));
	}

	FileInputStream digits(fn.name());
	CheckOnDigits(digits);
}

BOOST_AUTO_TEST_CASE(TestMemoryOutputStream)
{
	MemoryOutputStream s;
	BOOST_CHECK(s.GetData().empty());

	BOOST_CHECK_NO_THROW(s.WriteByte(7));
	BOOST_CHECK_EQUAL(s.GetData(), vec({7}));
	
	vec block{ 4, 2, 1, 7};
	BOOST_CHECK_NO_THROW(s.WriteBlock(block.data(), block.size()));

	BOOST_CHECK_EQUAL(s.GetData(), vec({7, 4, 2, 1, 7}));

	BOOST_CHECK_NO_THROW(s.WriteBlock(nullptr, 0));
}


BOOST_AUTO_TEST_SUITE_END()
