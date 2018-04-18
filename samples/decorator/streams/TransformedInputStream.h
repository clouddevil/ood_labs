#pragma once
#include "IInputDataStream.h"
#include "IStreamDataTransform.h"


class TransformedInputStream
	: public IInputDataStream
{
public:
	TransformedInputStream(IInputDataStreamUniquePtr&& stream, IStreamDataTransformPtr&& transform);

	bool IsEOF() const override;
	uint8_t ReadByte() override;
	std::streamsize ReadBlock(void * dstBuffer, std::streamsize size) override;

private:
	IInputDataStreamUniquePtr m_stream;
	IStreamDataTransformPtr m_transform;
};

