#include "stdafx.h"
#include "FileOutputStream.h"

FileOutputStream::FileOutputStream(std::string const& filename)
	: m_stream(filename, std::ios_base::binary)
{
	m_stream.exceptions(std::ios::failbit | std::ios::badbit);
}

void FileOutputStream::WriteByte(uint8_t data)
{
	m_stream.put(data);
}

void FileOutputStream::WriteBlock(const void * srcData, std::streamsize size)
{
	m_stream.write(reinterpret_cast<const char*>(srcData), size);
}

