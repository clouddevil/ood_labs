#pragma once
#include "ICanvas.h"

class SvgCanvas final
	: public ICanvas
{
public:
	SvgCanvas(std::string const& svgFileName);
	
	void BeginDraw(uint32_t w, uint32_t h);
	void EndDraw();	

	void SetDrawingState(CanvasDrawingState const& state) override;
	void DrawPolygon(std::vector<PointD> const& vtxs) override;

private:
	std::string GetStyle() const;

private:
	std::ofstream m_stream;
	CanvasDrawingState m_state;	
	std::string m_svgFileName;
};

