#include "stdafx.h"
#include "FileInputStream.h"

FileInputStream::FileInputStream(std::string const& filename)
	: m_stream(filename, std::ios_base::binary)
{
	m_stream.exceptions(std::ios::failbit | std::ios::badbit);
	m_stream.peek();
}

bool FileInputStream::IsEOF() const
{
	return m_stream.eof();
}

uint8_t FileInputStream::ReadByte()
{
	auto byte = m_stream.get();
	m_stream.peek();
	return byte;
}

std::streamsize FileInputStream::ReadBlock(void * dstBuffer, std::streamsize size)
{
	auto dstSize = m_stream.readsome(reinterpret_cast<char*>(dstBuffer), size);	
	m_stream.peek();
	return dstSize;
}
