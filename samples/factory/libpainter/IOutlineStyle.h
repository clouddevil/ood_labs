#pragma once
#include "CommonTypes.h"

class IOutlineStyle
{
public:
	virtual boost::optional<RGBAColor> GetColor()const = 0;
	virtual void SetColor(RGBAColor color) = 0;

	virtual boost::optional<float> GetThickness()const = 0;
	virtual void SetThickness(float thickness) = 0;

	virtual ~IOutlineStyle() = default;
};
