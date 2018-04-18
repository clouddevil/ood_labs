#include "stdafx.h"
#include "RLEOutputStream.h"

namespace
{

struct rle
{
	rle(uint8_t byte, uint8_t byteCount)
		: ch(byte)
		, size(byteCount)
	{
	}

	uint8_t ch = 0;
	uint8_t size = 0;
};

struct RlePairArray
{
	void AddByte(uint8_t byte)
	{		
		pairs.emplace_back(rle{ byte, 1 });
	}

	std::vector<rle> pairs;
};

}


RLEOutputStream::RLEOutputStream(std::string const& filename)
	: m_file(filename)
{
}

RLEOutputStream::~RLEOutputStream()
{
	TryCompress(true);
}

void RLEOutputStream::WriteByte(uint8_t data)
{
	m_buffer.WriteByte(data);
	TryCompress(false);
}

void RLEOutputStream::WriteBlock(const void * srcData, std::streamsize size)
{
	m_buffer.WriteBlock(srcData, size);
	TryCompress(false);
}

void RLEOutputStream::TryCompress(bool closeStream)
{
	auto data = m_buffer.GetData();
	
	RlePairArray rle;
	for (auto byte : data)
	{
		rle.AddByte(byte);
	}

	if (closeStream)
	{
		m_buffer.FitToSize(0);
	}
	else
	{
		auto lastRun = rle.pairs.rbegin();
		m_buffer.FitToSize(lastRun->size);

		rle.pairs.pop_back();
	}

	for (auto& p : rle.pairs)
	{
		m_file.WriteByte(p.ch);
		m_file.WriteByte(p.size);
	}
}
