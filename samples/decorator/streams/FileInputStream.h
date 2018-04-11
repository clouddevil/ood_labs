#pragma once
#include "IInputDataStream.h"


class FileInputStream
	: public IInputDataStream
{
public:
	FileInputStream(std::string const& filename);
	
	bool IsEOF() const override;
	uint8_t ReadByte() override;
	std::streamsize ReadBlock(void * dstBuffer, std::streamsize size) override;

private:
	std::ifstream m_stream;
};

	