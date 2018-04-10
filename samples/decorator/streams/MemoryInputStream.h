#pragma once
#include "IInputDataStream.h"

class MemoryInputStream
	: public IInputDataStream
{
public:
	MemoryInputStream(std::string const& data);

	bool IsEOF() const override;
	uint8_t ReadByte() override;
	std::streamsize ReadBlock(void * dstBuffer, std::streamsize size) override;

private:	
	std::istringstream m_stream;
};

