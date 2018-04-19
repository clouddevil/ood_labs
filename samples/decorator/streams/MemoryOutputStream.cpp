#include "stdafx.h"
#include "MemoryOutputStream.h"



void MemoryOutputStream::WriteByte(uint8_t data)
{
	m_buffer.push_back(data);
}

void MemoryOutputStream::WriteBlock(const void * srcData, std::streamsize size)
{
	auto srcDataSize = static_cast<uint32_t>(size);
	if (srcDataSize > 0)
	{
		auto bufferSize = m_buffer.size();
		m_buffer.resize(bufferSize + srcDataSize);
		memcpy(&m_buffer[bufferSize], srcData, srcDataSize);
	}	
}

void MemoryOutputStream::FitToSize(uint32_t size)
{
	auto bufferSize = std::min<uint32_t>(size, static_cast<uint32_t>(m_buffer.size()));
	std::vector<uint8_t>(m_buffer.end() - bufferSize, m_buffer.end()).swap(m_buffer);
}

std::vector<uint8_t> const& MemoryOutputStream::GetData() const
{
	return m_buffer;
}
