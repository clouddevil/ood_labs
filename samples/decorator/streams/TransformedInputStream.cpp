#include "stdafx.h"
#include "TransformedInputStream.h"


TransformedInputStream::TransformedInputStream(IInputDataStreamPtr const& stream, IStreamDataTransformPtr const& transform)
	: m_stream(stream)
	, m_transform(transform)
{
}

bool TransformedInputStream::IsEOF() const
{
	return m_stream->IsEOF();
}

uint8_t TransformedInputStream::ReadByte()
{
	return m_transform->Transform(m_stream->ReadByte());
}

std::streamsize TransformedInputStream::ReadBlock(void * dstBuffer, std::streamsize size)
{
	auto bytesRead = m_stream->ReadBlock(dstBuffer, size);
	uint8_t* buffer = reinterpret_cast<uint8_t*>(dstBuffer);
	for (auto i = 0; i < bytesRead; ++i)
	{
		buffer[i] = m_transform->Transform(buffer[i]);
	}
	return bytesRead;
}
