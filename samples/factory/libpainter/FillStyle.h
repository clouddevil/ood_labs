#pragma once
#include "IFillStyle.h"

class FillStyle
	: public IFillStyle
{
public:
	boost::optional<RGBAColor> GetColor() const override
	{
		return m_color;
	}

	void SetColor(RGBAColor color) override
	{
		m_color = color;
	}

private:
	boost::optional<RGBAColor> m_color;
};

