#pragma once
#include "ICanvas.h"

class SvgCanvas final
	: public ICanvas
{
public:
	SvgCanvas(std::string const& svgFileName);
	
	void SetDrawingState(CanvasDrawingState const& state) override;

	void DrawVertices(std::vector<PointD> const& vtxs) override;

private:
	std::ofstream m_stream;
	CanvasDrawingState m_state;	
};

