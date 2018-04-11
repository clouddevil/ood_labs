#include "stdafx.h"
#include "MemoryOutputStream.h"


void MemoryOutputStream::WriteByte(uint8_t data)
{
	m_stream.put(data);
}

void MemoryOutputStream::WriteBlock(const void * srcData, std::streamsize size)
{
	m_stream.write(reinterpret_cast<const char*>(srcData), size);
}

std::string MemoryOutputStream::GetStr() const
{
	return m_stream.str();
}
