#include "stdafx.h"
#include "MemoryInputStream.h"



MemoryInputStream::MemoryInputStream()
{
}

MemoryInputStream::~MemoryInputStream()
{
}

bool MemoryInputStream::IsEOF() const
{
	throw std::logic_error("The method or operation is not implemented.");
}

uint8_t MemoryInputStream::ReadByte()
{
	throw std::logic_error("The method or operation is not implemented.");
}

std::streamsize MemoryInputStream::ReadBlock(void * dstBuffer, std::streamsize size)
{
	throw std::logic_error("The method or operation is not implemented.");
}

