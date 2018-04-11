#pragma once
#include "IInputDataStream.h"
#include "StreamDataTransform.h"


class TransformedInputDataStream
	: public IInputDataStream
{
public:
	TransformedInputDataStream(IInputDataStreamUniquePtr&& stream, StreamDataTransformPtr&& transform);

	bool IsEOF() const override;
	uint8_t ReadByte() override;
	std::streamsize ReadBlock(void * dstBuffer, std::streamsize size) override;

private:
	IInputDataStreamUniquePtr m_stream;
	StreamDataTransformPtr m_transform;
};

