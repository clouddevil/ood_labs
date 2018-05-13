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
	void DrawEllipse(PointD const& center, PointD const& radius) override;

private:
	std::string GetStyle() const;

private:
	std::string m_svgFileName;
	std::ofstream m_stream;

	CanvasDrawingState m_state;		
};

