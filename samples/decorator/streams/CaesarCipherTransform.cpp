#include "stdafx.h"
#include "CaesarCipherTransform.h"



CaesarCipherTransform::CaesarCipherTransform(bool decrypt, unsigned int key)
	: m_table(256)
	, m_decrypt(decrypt)
{
	GenerateTable(key);
}

uint8_t CaesarCipherTransform::Transform(uint8_t byte)
{
	return m_table[byte];
}

void CaesarCipherTransform::GenerateTable(unsigned seed)
{
	std::iota(m_table.begin(), m_table.end(), 0);	
	std::shuffle(m_table.begin(), m_table.end(), std::default_random_engine(seed));

	if (m_decrypt)
	{
		std::sort(m_table.begin(), m_table.end(), [copy = m_table](const uint8_t& lhs, const uint8_t& rhs) {
			return copy[lhs] < copy[rhs];
		});
	}
}
