#include "stdafx.h"
#include "SvgCanvas.h"
#include <boost\format.hpp>


SvgCanvas::SvgCanvas(std::string const& svgFileName)
	: m_svgFileName(svgFileName)
{	
}

void SvgCanvas::DrawPolygon(std::vector<PointD> const& txs)
{
	std::ostringstream points;
	for (auto& pt : txs)
	{
		points << pt.x << "," << pt.y << " ";
	}	

	m_stream << boost::format(R"(<polygon points="%s" %s />)") % points.str() % GetStyle();	
	m_stream << std::endl;
}

void SvgCanvas::DrawEllipse(PointD const& c, PointD const& r)
{
	m_stream << boost::format(R"(<ellipse cx="%s" cy="%s" rx="%s" ry="%s" %s />)") % c.x % c.y % r.x % r.y % GetStyle();
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
		
	m_stream << boost::format(R"(<svg width="%s" height="%s" viewBox="0 0 %s %s" xmlns="http://www.w3.org/2000/svg">)") % w % h % w % h;
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
