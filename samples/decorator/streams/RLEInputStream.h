#pragma once
#include "IInputDataStream.h"
#include "MemoryInputStream.h"

class RLEInputStream
	: public IInputDataStream
{
public:
	RLEInputStream(IInputDataStreamPtr const& stream);

	bool IsEOF() const override;
	uint8_t ReadByte() override;
	std::streamsize ReadBlock(void * dstBuffer, std::streamsize size) override;

private:	
	void TryDecompress(std::streamsize size);

private:	
	MemoryInputStream m_buffer;
	IInputDataStreamPtr m_stream;
};

