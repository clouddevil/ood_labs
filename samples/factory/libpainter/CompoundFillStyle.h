#pragma once
#include "IFillStyle.h"

class CompoundFillStyle
	: public IFillStyle
{
public:
	boost::optional<RGBAColor> GetColor() const override
	{
		throw std::logic_error("The method or operation is not implemented.");
	}

	void SetColor(RGBAColor /*color*/) override
	{
		throw std::logic_error("The method or operation is not implemented.");
	}
};


