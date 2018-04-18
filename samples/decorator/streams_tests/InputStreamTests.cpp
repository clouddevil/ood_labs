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

BOOST_AUTO_TEST_CASE(TestMemoryInputStream)
{
	MemoryInputStream s;
	BOOST_CHECK_NO_THROW(s.SetData(vec(digits)));
	BOOST_CHECK_EQUAL(s.GetAvailableSize(), 10);
	BOOST_CHECK_EQUAL(s.ReadByte(), '0');
	BOOST_CHECK_EQUAL(s.GetAvailableSize(), 9);	

	BOOST_CHECK_NO_THROW(s.SetData(vec(digits)));
	BOOST_CHECK_EQUAL(s.GetAvailableSize(), 10);

	BOOST_CHECK_EQUAL(s.ReadByte(), '0');

	BOOST_CHECK_NO_THROW(s.FitToSize());

	auto availableSize = static_cast<uint32_t>(s.GetAvailableSize());
	BOOST_CHECK_EQUAL(availableSize, 9);

	vec buffer(2 * availableSize);
	BOOST_CHECK_NO_THROW(s.ReadBlock(buffer.data(), 2 * availableSize));

	BOOST_CHECK_NO_THROW(s.FitToSize());
	BOOST_CHECK_EQUAL(s.GetAvailableSize(), 0);
	
	BOOST_CHECK_NO_THROW(s.Append(digits));
	BOOST_CHECK_EQUAL(s.GetAvailableSize(), 10);

	BOOST_CHECK_EQUAL(s.ReadBlock(buffer.data(), 12), 10);
}


BOOST_AUTO_TEST_SUITE_END()
