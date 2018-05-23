#pragma once
#include "CommonTypes.h"

class IFillStyle
{
public:	
	virtual boost::optional<RGBAColor> GetColor()const = 0;
	virtual void SetColor(RGBAColor color) = 0;

	virtual ~IFillStyle() = default;
};

