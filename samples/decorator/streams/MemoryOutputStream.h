#pragma once
#include "IOutputDataStream.h"

class MemoryOutputStream
	: public IOutputDataStream
{
public:
	void WriteByte(uint8_t data) override;
	void WriteBlock(const void * srcData, std::streamsize size) override;

	void FitToSize(uint32_t size);
	std::vector<uint8_t> const& GetData() const;

private:
	std::vector<uint8_t> m_buffer;
};

