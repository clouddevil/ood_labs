#pragma once
#include "IOutputDataStream.h"
#include "IStreamDataTransform.h"


class TransformedOutputStream
	: public IOutputDataStream
{
public:
	TransformedOutputStream(IOutputDataStreamUniquePtr&& stream, IStreamDataTransformPtr&& transform);	

	void WriteByte(uint8_t data) override;
	void WriteBlock(const void * srcData, std::streamsize size) override;

private:
	IOutputDataStreamUniquePtr m_stream;
	IStreamDataTransformPtr m_transform;
};

