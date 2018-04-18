#include "stdafx.h"
#include "..\streams\RLEInputStream.h"
#include "StreamTestFunctions.h"
#include "..\streams\RLEOutputStream.h"

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

	std::shared_ptr<MemoryInputStream> inStream = ConstructDataInput();
	std::shared_ptr<MemoryOutputStream> outStream = std::make_unique<MemoryOutputStream>();

	std::shared_ptr<MemoryInputStream> ConstructDataInput()
	{
		auto ins = std::make_shared<MemoryInputStream>();
		BOOST_CHECK_NO_THROW(ins->SetData(vec(data)));
		return ins;
	}

	IInputDataStreamPtr ConstructRLEInput()
	{
		return std::make_shared<RLEInputStream>(inStream);
	}

	IOutputDataStreamPtr ConstructRLEOutput()
	{		
		return std::make_shared<RLEOutputStream>(outStream);
	}	
};


}

BOOST_FIXTURE_TEST_SUITE(RLEStreamTestSuite, RLEStreamFixture)

BOOST_AUTO_TEST_CASE(TestRLEInputStreamReadBlock)
{	
	auto s = ConstructRLEInput();

	vec iData(10, 42);
	BOOST_CHECK_NO_THROW(s->ReadBlock(iData.data(), iData.size()));
	BOOST_CHECK(s->IsEOF());
	BOOST_CHECK_EQUAL(iData, vec({ 9, 4, 4, 4, 6, 0, 0, 7, 42, 42 }));
}

BOOST_AUTO_TEST_CASE(TestRLEInputStreamReadByte)
{
	auto s = ConstructRLEInput();

	BOOST_CHECK_EQUAL(s->ReadByte(), 9);
	BOOST_CHECK_EQUAL(s->ReadByte(), 4);
	BOOST_CHECK_EQUAL(s->ReadByte(), 4);
	BOOST_CHECK_EQUAL(s->ReadByte(), 4);
	BOOST_CHECK_EQUAL(s->ReadByte(), 6);
	BOOST_CHECK_EQUAL(s->ReadByte(), 0);
	BOOST_CHECK(!s->IsEOF());	
}

BOOST_AUTO_TEST_CASE(TestRLEOutputStreamWriteByte)
{	
	{
		auto s = ConstructRLEOutput();
		BOOST_CHECK_NO_THROW(s->WriteByte(9));
		BOOST_CHECK_EQUAL(outStream->GetData(), vec({}));

		BOOST_CHECK_NO_THROW(s->WriteByte(4));
		BOOST_CHECK_EQUAL(outStream->GetData(), vec({9, 1}));

		BOOST_CHECK_NO_THROW(s->WriteByte(4));
		BOOST_CHECK_EQUAL(outStream->GetData(), vec({ 9, 1 }));

		BOOST_CHECK_NO_THROW(s->WriteByte(4));
		BOOST_CHECK_EQUAL(outStream->GetData(), vec({ 9, 1 }));

		BOOST_CHECK_NO_THROW(s->WriteByte(6));
		BOOST_CHECK_EQUAL(outStream->GetData(), vec({ 9, 1, 4, 3 }));

		BOOST_CHECK_NO_THROW(s->WriteByte(0));
		BOOST_CHECK_EQUAL(outStream->GetData(), vec({ 9, 1, 4, 3, 6, 1 }));

		BOOST_CHECK_NO_THROW(s->WriteByte(0));
		BOOST_CHECK_EQUAL(outStream->GetData(), vec({ 9, 1, 4, 3, 6, 1 }));

		BOOST_CHECK_NO_THROW(s->WriteByte(7));
		BOOST_CHECK_EQUAL(outStream->GetData(), vec({ 9, 1, 4, 3, 6, 1, 0, 2 }));
	}
	auto const& outData = outStream->GetData();
	BOOST_CHECK_EQUAL(outData, data);
}

BOOST_AUTO_TEST_CASE(TestRLEWriteBlock)
{
	{
		auto s = ConstructRLEOutput();
		BOOST_CHECK_NO_THROW(s->WriteBlock(nullptr, 0));
		BOOST_CHECK_NO_THROW(s->WriteBlock(vec({9, 4, 4, 4, 6, 0, 0, 7}).data(), 8));
	}
	auto const& outData = outStream->GetData();
	BOOST_CHECK_EQUAL(outData, data);
}

BOOST_AUTO_TEST_CASE(TestRLEComplexTest)
{
	vec buffer;
	{
		std::string s = "long long       sssssssttttttinnnnngg to tteeesst rle compppppressiion         ";		
		std::copy(s.begin(), s.end(), std::back_inserter(buffer));		
	}

	// compress
	{
		auto out = ConstructRLEOutput();
		out->WriteBlock(buffer.data(), buffer.size());
	}

	vec result;

	// decompress
	{
		auto inp = ConstructRLEInput();
		inStream->SetData(vec(outStream->GetData()));
		while (!inp->IsEOF())
		{
			vec tmp(7);
			auto readSize = inp->ReadBlock(tmp.data(), tmp.size());
			tmp.resize(static_cast<uint32_t>(readSize));

			result.insert(result.end(), tmp.begin(), tmp.end());
		}
	}
	BOOST_CHECK_EQUAL(buffer, result);
}

BOOST_AUTO_TEST_SUITE_END()
