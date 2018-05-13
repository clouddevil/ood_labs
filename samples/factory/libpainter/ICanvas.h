#pragma once
#include "CommonTypes.h"

struct CanvasDrawingState
{	
	boost::optional<float> outlineThin;
	boost::optional<RGBAColor> outlineColor;
	
	boost::optional<RGBAColor> fillColor;
};


class ICanvas
{
public:
	virtual void SetDrawingState(CanvasDrawingState const& state) = 0;
	
	virtual void DrawPolygon(std::vector<PointD> const& vtxs) = 0;
	virtual void DrawEllipse(PointD const& center, PointD const& radius) = 0;	
};

