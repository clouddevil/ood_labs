#pragma once
#include "IOutputDataStream.h"
#include "FileOutputStream.h"
#include "MemoryOutputStream.h"

class RLEOutputStream
	: public IOutputDataStream
{
public:
	RLEOutputStream(std::string const& filename);
	~RLEOutputStream();

	void WriteByte(uint8_t data) override;
	void WriteBlock(const void * srcData, std::streamsize size) override;

private:
	void TryCompress(bool closeStream);	

private:
	FileOutputStream m_file;
	MemoryOutputStream m_buffer;	
};

