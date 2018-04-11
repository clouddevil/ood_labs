#pragma once
#include "StreamDataTransform.h"

class CaesarCipherTransform
	: public StreamDataTransform
{
public:
	CaesarCipherTransform(bool decrypt);

	uint8_t Transform(uint8_t byte) override;

private:
	void GenerateTable(unsigned seed);

private:	
	bool m_decrypt = false;

	std::vector<uint8_t> m_table;
};

