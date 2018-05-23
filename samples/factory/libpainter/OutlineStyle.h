#pragma once
#include "IOutlineStyle.h"

class OutlineStyle
	: public IOutlineStyle
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

	boost::optional<float> GetThickness() const override
	{
		return m_thickness;
	}

	void SetThickness(float thickness) override
	{
		m_thickness = thickness;
	}

private:
	boost::optional<float> m_thickness;
	boost::optional<RGBAColor> m_color;
};
