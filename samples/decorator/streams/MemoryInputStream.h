#pragma once
#include "IInputDataStream.h"

class MemoryInputStream
	: public IInputDataStream
{
public:	
	bool IsEOF() const override;
	uint8_t ReadByte() override;
	std::streamsize ReadBlock(void * dstBuffer, std::streamsize size) override;
	
	void FitToSize();
	void Append(std::vector<uint8_t> const& data);
	void SetData(std::vector<uint8_t>&& data);

	std::streamsize GetAvailableSize() const;
	
private:
	uint32_t m_pos = 0;
	std::vector<uint8_t> m_buffer;
};

