#pragma once


struct LineStyle
{
	float thin = 0.0f;
	boost::optional<uint32_t> fillColor;
};

struct FillStyle
{
	boost::optional<uint32_t> fillColor;
};


using LineStylePtr = std::shared_ptr<LineStyle>;
using FillStylePtr = std::shared_ptr<FillStyle>;
