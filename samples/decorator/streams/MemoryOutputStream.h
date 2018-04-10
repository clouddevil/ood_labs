#pragma once
#include "IOutputDataStream.h"

class MemoryOutputStream
	: public IOutputDataStream
{
public:
	MemoryOutputStream();	

	void WriteByte(uint8_t data) override;
	void WriteBlock(const void * srcData, std::streamsize size) override;
};

