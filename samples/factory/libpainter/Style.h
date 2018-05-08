#pragma once


struct LineStyle
{
	float thin = 1.0f;
	DWORD color = 0x00;
};

struct FillStyle
{
	DWORD color = 0x00;
};


using LineStylePtr = std::shared_ptr<LineStyle>;
using FillStylePtr = std::shared_ptr<FillStyle>;