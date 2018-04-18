#pragma once
#include "IStreamDataTransform.h"

class CaesarCipherTransform
	: public IStreamDataTransform
{
public:
	CaesarCipherTransform(bool decrypt, unsigned int key = 42);

	uint8_t Transform(uint8_t byte) override;

private:
	void GenerateTable(unsigned seed);

private:	
	bool m_decrypt = false;

	std::vector<uint8_t> m_table;
};

