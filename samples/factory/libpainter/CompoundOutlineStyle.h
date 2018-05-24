#pragma once
#include "IOutlineStyle.h"
#include "IShape.h"
#include "OutlineStyle.h"

class IOutlineStyleProvider
{
public:
	virtual uint32_t GetOutlineStyleCount() const = 0;
	virtual IOutlineStyle& GetOutlineStyle(uint32_t index) const = 0;
};

class CompoundOutlineStyle
	: public IOutlineStyle
{
public:
	CompoundOutlineStyle(IOutlineStyleProvider const& provider)
		: m_provider(provider)
	{
	}

	boost::optional<RGBAColor> GetColor() const override
	{
		auto styleCount = m_provider.GetOutlineStyleCount();
		if (styleCount > 0)
		{
			auto const& s = m_provider.GetOutlineStyle(0);

			auto color = s.GetColor();
			for (auto i = 1u; i < styleCount; ++i)
			{
				auto& nextStyle = m_provider.GetOutlineStyle(i);
				if (color != nextStyle.GetColor())
				{
					return boost::none;
				}
			}
			return color;
		}
		return boost::none;
	}

	void SetColor(RGBAColor color) override
	{
		auto styleCount = m_provider.GetOutlineStyleCount();		
		for (auto i = 0u; i < styleCount; ++i)
		{
			auto& s = m_provider.GetOutlineStyle(i);
			s.SetColor(color);
		}
	}

	boost::optional<float> GetThickness() const override
	{
		auto styleCount = m_provider.GetOutlineStyleCount();
		if (styleCount > 0)
		{
			auto& s = m_provider.GetOutlineStyle(0);

			auto thickness = s.GetThickness();
			for (auto i = 1u; i < styleCount; ++i)
			{
				auto& nextStyle = m_provider.GetOutlineStyle(i);
				if (thickness != nextStyle.GetThickness())
				{
					return boost::none;
				}
			}
			return thickness;
		}
		return boost::none;
	}

	void SetThickness(float thickness) override
	{
		auto styleCount = m_provider.GetOutlineStyleCount();
		for (auto i = 0u; i < styleCount; ++i)
		{
			auto& s = m_provider.GetOutlineStyle(i);
			s.SetThickness(thickness);
		}
	}

private:
	IOutlineStyleProvider const& m_provider;
};
