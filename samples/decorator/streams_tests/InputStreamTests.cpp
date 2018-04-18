#include "stdafx.h"
#include "..\streams\FileInputStream.h"
#include "..\streams\MemoryInputStream.h"
#include "StreamTestFunctions.h"

namespace
{

struct InputStreamFixture
	: BaseFixture
{
};


}

BOOST_FIXTURE_TEST_SUITE(InputStreamTestSuite, InputStreamFixture)

BOOST_AUTO_TEST_CASE(TestThrowOnNoFile)
{
	BOOST_CHECK_THROW(FileInputStream s("empty_file_not_exist.txt"), std::ios_base::failure);	
}

BOOST_AUTO_TEST_CASE(TestOnEmptyFile)
{
	FileInputStream s("empty.txt");
	CheckOnEmptyData(s);	
}

BOOST_AUTO_TEST_CASE(TestOnDigitsFile)
{
	FileInputStream s("digits.txt");
	CheckOnDigits(s);
}

BOOST_AUTO_TEST_CASE(TestOnEmptyData)
{
	MemoryInputStream s;
	s.SetData({});
	CheckOnEmptyData(s);
}

BOOST_AUTO_TEST_CASE(TestOnDigitsData)
{
	MemoryInputStream s;
	s.SetData(vec(digits));
 	CheckOnDigits(s);
}

BOOST_AUTO_TEST_SUITE_END()
