#include "stdafx.h"
#include "RLEInputStream.h"

RLEInputStream::RLEInputStream(std::string const& filename)
	: m_file(filename)	
{
}

bool RLEInputStream::IsEOF() const
{	
	return m_buffer.IsEOF() && m_file.IsEOF();
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
	while (!m_file.IsEOF() && (m_buffer.GetAvailableSize() < size))
	{
		const auto byte = m_file.ReadByte();
		const auto byteCount = m_file.ReadByte();

		std::vector<uint8_t> data(byteCount, byte);
		m_buffer.Append(data);
	}
	m_buffer.FitToSize();
}
