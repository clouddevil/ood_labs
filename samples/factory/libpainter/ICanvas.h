#pragma once
#include "CommonTypes.h"

struct CanvasDrawingState
{	
	boost::optional<int> outlineThin;
	boost::optional<RGBAColor> outlineColor;
	
	boost::optional<RGBAColor> fillColor;
};


class ICanvas
{
public:	
	virtual void SetDrawingState(CanvasDrawingState const& state) = 0;
	
	virtual void DrawVertices(std::vector<PointD> const& vtxs) = 0;
	//virtual void DrawRect(Point const& l, Point const& t, Point const& w, Point const& h) = 0;
	//virtual void DrawEllipse(Point const& l, Point const& t, Point const& w, Point const& h) = 0;
};

