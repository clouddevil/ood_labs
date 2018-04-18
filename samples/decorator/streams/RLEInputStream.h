#pragma once
#include "IInputDataStream.h"
#include "FileInputStream.h"
#include "MemoryInputStream.h"

class RLEInputStream
	: public IInputDataStream
{
public:
	RLEInputStream(std::string const& filename);

	bool IsEOF() const override;
	uint8_t ReadByte() override;
	std::streamsize ReadBlock(void * dstBuffer, std::streamsize size) override;

private:	
	void TryDecompress(std::streamsize size);

private:
	FileInputStream m_file;
	MemoryInputStream m_buffer;
};

