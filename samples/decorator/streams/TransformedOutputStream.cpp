#include "stdafx.h"
#include "TransformedOutputStream.h"


TransformedOutputStream::TransformedOutputStream(IOutputDataStreamUniquePtr&& stream, IStreamDataTransformPtr&& transform)
	: m_stream(std::move(stream))
	, m_transform(std::move(transform))
{
}

void TransformedOutputStream::WriteByte(uint8_t data)
{
	m_stream->WriteByte(m_transform->Transform(data));
}

void TransformedOutputStream::WriteBlock(const void * srcData, std::streamsize size)
{
	auto srcBuffer = reinterpret_cast<const uint8_t*>(srcData);

	std::vector<uint8_t> tmpBuffer(static_cast<unsigned int>(size), 0);
	for (auto i = 0; i < size; ++i)
	{
		tmpBuffer[i] = m_transform->Transform(srcBuffer[i]);
	}
	m_stream->WriteBlock(tmpBuffer.data(), size);	
}
