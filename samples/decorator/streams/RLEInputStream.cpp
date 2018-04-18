#include "stdafx.h"
#include "RLEInputStream.h"

RLEInputStream::RLEInputStream(IInputDataStreamPtr const& stream)
	: m_stream(stream)
{
	if (!m_stream)
	{
		throw std::runtime_error("");
	}
}

bool RLEInputStream::IsEOF() const
{	
	return m_buffer.IsEOF() && m_stream->IsEOF();
}

uint8_t RLEInputStream::ReadByte()
{
	TryDecompress(1);
	return m_buffer.ReadByte();	
}

std::streamsize RLEInputStream::ReadBlock(void* dstBuffer, std::streamsize size)
{
	TryDecompress(size);
	return m_buffer.ReadBlock(dstBuffer, size);
}

void RLEInputStream::TryDecompress(std::streamsize size)
{
	while (!m_stream->IsEOF() && (m_buffer.GetAvailableSize() < size))
	{
		const auto byte = m_stream->ReadByte();
		const auto byteCount = m_stream->ReadByte();
		m_buffer.Append(std::vector<uint8_t>(byteCount, byte));
	}
	m_buffer.FitToSize();
}
