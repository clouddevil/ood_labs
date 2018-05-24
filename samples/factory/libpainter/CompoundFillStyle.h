#pragma once
#include "IFillStyle.h"

class IFillStyleProvider
{
public:
	virtual uint32_t GetFillStyleCount() const = 0;
	virtual IFillStyle& GetFillStyle(uint32_t index) const = 0;
};

class CompoundFillStyle
	: public IFillStyle
{
public:
	CompoundFillStyle(IFillStyleProvider const& provider)
		: m_provider(provider)
	{
	}

	boost::optional<RGBAColor> GetColor() const override
	{
		auto styleCount = m_provider.GetFillStyleCount();
		if (styleCount > 0)
		{
			auto const& s = m_provider.GetFillStyle(0);

			auto color = s.GetColor();
			for (auto i = 1u; i < styleCount; ++i)
			{
				auto& nextStyle = m_provider.GetFillStyle(i);
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
		auto styleCount = m_provider.GetFillStyleCount();
		for (auto i = 0u; i < styleCount; ++i)
		{
			auto& s = m_provider.GetFillStyle(i);
			s.SetColor(color);
		}
	}

private:
	IFillStyleProvider const& m_provider;
};


