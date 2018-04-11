#pragma once


class StreamDataTransform
{
public:
	virtual uint8_t Transform(uint8_t byte)
	{
		return byte;
	}

	virtual ~StreamDataTransform() = default;
};


using StreamDataTransformPtr = std::unique_ptr<StreamDataTransform>;
