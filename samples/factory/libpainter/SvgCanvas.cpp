#include "stdafx.h"
#include "SvgCanvas.h"
#include <boost\format.hpp>

namespace
{

int LoByte(int color)
{
	return color & 0xFF;
}

std::string ColorToString(RGBAColor color)
{
	int r = LoByte(color >> 16);
	int g = LoByte(color >> 8);
	int b = LoByte(color >> 0);

	return (boost::format(R"(rgb(%s,%s,%s))") % r % g % b).str();
}

std::string AlphaToString(RGBAColor color)
{
	int alpha = 255 - LoByte(color >> 24);
	return std::to_string(alpha / 255.0f);
}

}

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
		
	constexpr RGBAColor BackgroundColor = 0xDDDDDD;
	m_stream << boost::format(R"(<svg width="%s" height="%s" viewBox="0 0 %s %s" xmlns="http://www.w3.org/2000/svg">)") % w % h % w % h;
	m_stream << std::endl;

	m_stream << boost::format(R"(<rect x="0" y="0" width="%s" height="%s" style="fill:%s;" />)") % w % h % ColorToString(BackgroundColor);
	m_stream << std::endl;
}

void SvgCanvas::EndDraw()
{
	m_stream << "</svg>";
	m_stream.close();
}

std::string SvgCanvas::GetStyle() const
{
	std::ostringstream cssStyle;
	if (m_state.fillColor)
	{
		auto c = m_state.fillColor.get();
		cssStyle << "fill:" << ColorToString(c) << ";";
		cssStyle << "fill-opacity:" << AlphaToString(c) << ";";
	}
	if (m_state.outlineColor)
	{
		auto c = m_state.outlineColor.get();
		cssStyle << "stroke:" << ColorToString(c) << ";";
		cssStyle << "stroke-opacity:" << AlphaToString(c) << ";";
	}
	if (m_state.outlineThin)
	{
		cssStyle << "stroke-width:" << m_state.outlineThin.get() << ";";
	}

	return (boost::format(R"( style="%s")") % cssStyle.str()).str();	
}
