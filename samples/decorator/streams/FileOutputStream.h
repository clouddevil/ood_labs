#pragma once
#include "IOutputDataStream.h"


class FileOutputStream
	: public IOutputDataStream
{
public:
	FileOutputStream(std::string const& filename);

	void WriteByte(uint8_t data) override;
	void WriteBlock(const void * srcData, std::streamsize size) override;

private:
	std::ofstream m_stream;
};

