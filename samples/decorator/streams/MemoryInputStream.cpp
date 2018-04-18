#include "stdafx.h"
#include "MemoryInputStream.h"

bool MemoryInputStream::IsEOF() const
{
	return (GetAvailableSize() == 0);
}

uint8_t MemoryInputStream::ReadByte()
{	
	if (m_pos >= m_buffer.size())
	{
		throw std::ios_base::failure("");
	}
	return m_buffer[m_pos++];
}

std::streamsize MemoryInputStream::ReadBlock(void* dstBuffer, std::streamsize size)
{
	auto availableSize = static_cast<uint32_t>(std::min<>(size, GetAvailableSize()));
	if (availableSize == 0)
	{
		throw std::ios_base::failure("");
	}

	memcpy(dstBuffer, &m_buffer[m_pos], availableSize);
	m_pos += availableSize;
	return availableSize;
}

void MemoryInputStream::FitToSize()
{
	std::vector<uint8_t>(m_buffer.begin() + m_pos, m_buffer.end()).swap(m_buffer);
	m_pos = 0;
}

void MemoryInputStream::Append(std::vector<uint8_t> const& data)
{
	m_buffer.reserve(m_buffer.size() + data.size());
	m_buffer.insert(m_buffer.end(), data.begin(), data.end());
}

void MemoryInputStream::SetData(std::vector<uint8_t>&& data)
{	
	m_buffer.swap(data);
	m_pos = 0;
}

std::streamsize MemoryInputStream::GetAvailableSize() const
{
	return m_buffer.size() - m_pos;
}
