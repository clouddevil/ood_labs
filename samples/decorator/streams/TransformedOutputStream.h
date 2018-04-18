#pragma once
#include "IOutputDataStream.h"
#include "IStreamDataTransform.h"


class TransformedOutputStream
	: public IOutputDataStream
{
public:
	TransformedOutputStream(IOutputDataStreamPtr const& stream, IStreamDataTransformPtr const& transform);	

	void WriteByte(uint8_t data) override;
	void WriteBlock(const void * srcData, std::streamsize size) override;

private:
	IOutputDataStreamPtr m_stream;
	IStreamDataTransformPtr m_transform;
};

