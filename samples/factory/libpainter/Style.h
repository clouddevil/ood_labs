#pragma once

struct LineStyle;
struct FillStyle;

using LineStylePtr = std::shared_ptr<LineStyle>;
using FillStylePtr = std::shared_ptr<FillStyle>;

struct LineStyle
{
	float thin = 0.0f;
	uint32_t fillColor = 0;

	bool operator==(LineStyle const& rhs) const
	{
		const bool thinEquals = abs(thin - rhs.thin) < std::numeric_limits<float>::epsilon();
		return (thinEquals) && (fillColor == rhs.fillColor);
	}

	LineStylePtr Clone() const
	{
		return std::make_shared<LineStyle>(*this);
	}
};

struct FillStyle
{
	uint32_t fillColor = 0;

	bool operator==(FillStyle const& rhs) const
	{
		return (fillColor == rhs.fillColor);
	}

	FillStylePtr Clone() const
	{
		return std::make_shared<FillStyle>(*this);
	}
	
};



