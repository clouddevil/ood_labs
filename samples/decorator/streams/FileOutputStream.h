#pragma once
#include "IOutputDataStream.h"


class FileOutputStream
	: public IOutputDataStream
{
public:
	FileOutputStream();	

	void WriteByte(uint8_t data) override;
	void WriteBlock(const void * srcData, std::streamsize size) override;
};

