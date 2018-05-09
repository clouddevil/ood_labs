#include "stdafx.h"
#include "SvgCanvas.h"


SvgCanvas::SvgCanvas(std::string const& svgFileName)
	: m_svgFileName(svgFileName)
{	
}

void SvgCanvas::DrawPolygon(std::vector<PointD> const& txs)
{
	// <polygon points="0,100 50,25 50,75 100,0" />

	std::ostringstream points;
	for (auto& pt : txs)
	{
		points << pt.x << "," << pt.y << " ";
	}	

	m_stream << R"(<polygon points=")" << points.str() << R"(" )" << GetStyle() << R"( />)";
	m_stream << std::endl;
}

void SvgCanvas::SetDrawingState(CanvasDrawingState const& state)
{
	m_state = state;
}

void SvgCanvas::BeginDraw(uint32_t w, uint32_t h)
{
	m_stream.exceptions(std::ios::failbit | std::ios::badbit);
	m_stream.open(m_svgFileName, std::ios_base::out | std::ios_base::trunc);

	// <svg width="w" height="h" viewBox="0 0 w h" xmlns="http://www.w3.org/2000/svg">

	std::ostringstream viewbox;
	viewbox << "0 0 " << w << " " << h;

	std::ostringstream sizearg;
	sizearg << R"(width=")" << w << R"(" height=")" << h << R"(" )";

	m_stream << R"(<svg )" << sizearg.str() <<  R"(viewBox=")" << viewbox.str() << R"(" xmlns="http://www.w3.org/2000/svg">)";
	m_stream << std::endl;
}

void SvgCanvas::EndDraw()
{
	m_stream << "</svg>";	
	m_stream.close();
}

std::string SvgCanvas::GetStyle() const
{
	return R"(style="fill:blue;stroke:pink;stroke-width:5;opacity:0.5")";
}

