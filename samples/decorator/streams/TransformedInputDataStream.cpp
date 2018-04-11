#include "stdafx.h"
#include "TransformedInputDataStream.h"


TransformedInputDataStream::TransformedInputDataStream(IInputDataStreamUniquePtr&& stream, StreamDataTransformPtr&& transform)
	: m_stream(std::move(stream))
	, m_transform(std::move(transform))
{	
}

bool TransformedInputDataStream::IsEOF() const
{
	return m_stream->IsEOF();
}

uint8_t TransformedInputDataStream::ReadByte()
{
	return m_transform->Transform(m_stream->ReadByte());
}

std::streamsize TransformedInputDataStream::ReadBlock(void * dstBuffer, std::streamsize size)
{
	auto bytesRead = m_stream->ReadBlock(dstBuffer, size);
	uint8_t* buffer = reinterpret_cast<uint8_t*>(dstBuffer);
	for (auto i = 0; i < bytesRead; ++i)
	{
		buffer[i] = m_transform->Transform(buffer[i]);
	}
	return bytesRead;
}
