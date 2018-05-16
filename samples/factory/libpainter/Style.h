#pragma once


struct LineStyle
{
	float thin = 0.0f;
	uint32_t fillColor = 0;

	bool operator==(LineStyle const& rhs) const
	{
		const bool thinEquals = abs(thin - rhs.thin) < std::numeric_limits<float>::epsilon();
		return (thinEquals) && (fillColor == rhs.fillColor);
	}
};

struct FillStyle
{
	uint32_t fillColor = 0;

	bool operator==(FillStyle const& rhs) const
	{
		return (fillColor == rhs.fillColor);
	}
};


using LineStylePtr = std::shared_ptr<LineStyle>;
using FillStylePtr = std::shared_ptr<FillStyle>;
