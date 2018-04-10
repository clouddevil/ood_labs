#include "stdafx.h"
#include "FileInputStream.h"

FileInputStream::FileInputStream(std::string const& filename)
	: m_stream(filename)
{
	m_stream.exceptions(std::ios::failbit | std::ios::badbit);
}

bool FileInputStream::IsEOF() const
{
	return m_stream.eof();	
}

uint8_t FileInputStream::ReadByte()
{
	return m_stream.get();
}

std::streamsize FileInputStream::ReadBlock(void * dstBuffer, std::streamsize size)
{
	 return m_stream.readsome(reinterpret_cast<char*>(dstBuffer), size);
}
