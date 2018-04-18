#pragma once
#include "IOutputDataStream.h"
#include "MemoryOutputStream.h"

class RLEOutputStream
	: public IOutputDataStream
{
public:
	RLEOutputStream(IOutputDataStreamPtr const& stream);
	~RLEOutputStream();

	void WriteByte(uint8_t data) override;
	void WriteBlock(const void * srcData, std::streamsize size) override;

private:
	void TryCompress(bool closeStream);	

private:
	MemoryOutputStream m_buffer;
	IOutputDataStreamPtr m_stream;
};

