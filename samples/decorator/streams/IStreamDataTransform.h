#pragma once


class IStreamDataTransform
{
public:
	virtual uint8_t Transform(uint8_t byte) = 0;

	virtual ~IStreamDataTransform() = default;
};


using IStreamDataTransformPtr = std::shared_ptr<IStreamDataTransform>;
