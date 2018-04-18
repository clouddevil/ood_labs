#pragma once
#include "IInputDataStream.h"
#include "IStreamDataTransform.h"


class TransformedInputStream
	: public IInputDataStream
{
public:
	TransformedInputStream(IInputDataStreamPtr const& stream, IStreamDataTransformPtr const& transform);

	bool IsEOF() const override;
	uint8_t ReadByte() override;
	std::streamsize ReadBlock(void * dstBuffer, std::streamsize size) override;

private:
	IInputDataStreamPtr m_stream;
	IStreamDataTransformPtr m_transform;
};

