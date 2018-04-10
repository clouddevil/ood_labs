#include "stdafx.h"
#include "MemoryInputStream.h"


MemoryInputStream::MemoryInputStream(std::string const& data)
	: m_stream(data)
{
	m_stream.exceptions(std::ios::failbit | std::ios::badbit);
}

bool MemoryInputStream::IsEOF() const
{
	return m_stream.eof();
}

uint8_t MemoryInputStream::ReadByte()
{
	return m_stream.get();
}

std::streamsize MemoryInputStream::ReadBlock(void* dstBuffer, std::streamsize size)
{
	return m_stream.readsome(reinterpret_cast<char*>(dstBuffer), size);
}

