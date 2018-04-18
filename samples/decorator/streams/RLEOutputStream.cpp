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
		if (pairs.empty())
		{
			PutByte(byte);
		}
		else
		{
			auto last = pairs.rbegin();
			if (last->ch == byte)
			{
				if (last->size >= std::numeric_limits<uint8_t>::max())
				{
					PutByte(byte);
				}
				else
				{
					last->size++;
				}
			}
			else
			{
				PutByte(byte);
			}
		}		
	}

	void PutByte(uint8_t byte)
	{
		pairs.emplace_back(rle{ byte, 1 });
	}

	std::vector<rle> pairs;
};

}

RLEOutputStream::RLEOutputStream(IOutputDataStreamPtr const& stream)
	: m_stream(stream)
{
	if (!m_stream)
	{
		throw std::runtime_error("");
	}
}

RLEOutputStream::~RLEOutputStream()
{
	try
	{
		TryCompress(true);
	}
	catch (...)
	{
	}	
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
	auto const& bufferData = m_buffer.GetData();
	if (bufferData.empty())
	{
		return;
	}

	RlePairArray rle;
	for (auto byte : bufferData)
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

	MemoryOutputStream memory;
	for (auto& p : rle.pairs)
	{
		memory.WriteByte(p.ch);
		memory.WriteByte(p.size);
	}

	auto const& block = memory.GetData();
	m_stream->WriteBlock(block.data(), block.size());
}

