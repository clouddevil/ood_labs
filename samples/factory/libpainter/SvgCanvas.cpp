#include "stdafx.h"
#include "SvgCanvas.h"


SvgCanvas::SvgCanvas(std::string const& svgFileName)
	: m_stream(svgFileName)
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

