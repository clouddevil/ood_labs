#pragma once
#include "IOutputDataStream.h"

class MemoryOutputStream
	: public IOutputDataStream
{
public:	
	void WriteByte(uint8_t data) override;
	void WriteBlock(const void * srcData, std::streamsize size) override;

	std::string GetStr() const;

private:
	std::ostringstream m_stream;
};

