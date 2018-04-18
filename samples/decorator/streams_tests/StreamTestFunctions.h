#pragma once
#include "..\streams\IInputDataStream.h"

namespace
{

struct BaseFixture
{
	using vec = std::vector<uint8_t>;
	vec digits{ '0', '1', '2', '3', '4', '5', '6', '7', '8', '9' };
};


void CheckOnEmptyData(IInputDataStream& s)
{
	BOOST_CHECK(s.IsEOF());

	BOOST_CHECK_THROW(s.ReadByte(), std::ios_base::failure);
	BOOST_CHECK(s.IsEOF());

	std::vector<uint8_t> buffer(10);
	BOOST_CHECK_THROW(s.ReadBlock(buffer.data(), buffer.size()), std::ios_base::failure);
	BOOST_CHECK(s.IsEOF());
}

void CheckOnDigits(IInputDataStream& s)
{
	BOOST_CHECK(!s.IsEOF());

	auto value = -10;
	BOOST_CHECK_NO_THROW(value = s.ReadByte());
	BOOST_CHECK_EQUAL(value, '0');

	std::vector<uint8_t> buffer(10);
	std::streamsize len = 0;
	BOOST_CHECK_NO_THROW(len = s.ReadBlock(buffer.data(), buffer.size()));
	BOOST_CHECK_EQUAL(len, 9);
	BOOST_CHECK(s.IsEOF());

	std::vector<uint8_t> expectedBuffer(0);
	expectedBuffer = { '1', '2', '3', '4', '5', '6', '7', '8', '9', 0 };
	BOOST_CHECK(buffer == expectedBuffer);

	BOOST_CHECK_THROW(s.ReadBlock(buffer.data(), buffer.size()), std::ios_base::failure);
	BOOST_CHECK(s.IsEOF());
}



}