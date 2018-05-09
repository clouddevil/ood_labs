#include "stdafx.h"
#include "SvgCanvas.h"


SvgCanvas::SvgCanvas(std::string const& svgFileName)
	: m_svgFileName(svgFileName)
{	
}

void SvgCanvas::DrawVertices(std::vector<PointD> const& /*vtxs*/)
{
	throw std::logic_error("The method or operation is not implemented.");
}

void SvgCanvas::SetDrawingState(CanvasDrawingState const& state)
{
	m_state = state;
}

void SvgCanvas::BeginDraw(uint32_t w, uint32_t h)
{
	m_stream.exceptions(std::ios::failbit | std::ios::badbit);
	m_stream.open(m_svgFileName, std::ios_base::out | std::ios_base::trunc);

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

