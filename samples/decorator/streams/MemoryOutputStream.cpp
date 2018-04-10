#include "stdafx.h"
#include "MemoryOutputStream.h"

MemoryOutputStream::MemoryOutputStream()
{
}

void MemoryOutputStream::WriteByte(uint8_t data)
{
	throw std::logic_error("The method or operation is not implemented.");
}

void MemoryOutputStream::WriteBlock(const void * srcData, std::streamsize size)
{
	throw std::logic_error("The method or operation is not implemented.");
}
