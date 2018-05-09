#include "stdafx.h"
#include "DraftPainter.h"
#include "IPictureDraft.h"
#include "ICanvas.h"
#include "Shapes.h"

DraftPainter::DraftPainter(ICanvas& canvas)
	: m_canvas(canvas)
{
}

void DraftPainter::Visit(shape::Rectangle const& shape)
{
	SetCanvasShapeStyle(shape);
}

void DraftPainter::Visit(shape::Triangle const& shape)
{
	SetCanvasShapeStyle(shape);
}

void DraftPainter::Visit(shape::Ellipse const& shape)
{
	SetCanvasShapeStyle(shape);
}

void DraftPainter::SetCanvasShapeStyle(IShape const& /*shape*/)
{

	//m_canvas.SetFillColor()
}

void PaintDraft(IPictureDraft const& draft, ICanvas& canvas)
{	
	DraftPainter painter(canvas);
	for (auto const& shape : draft)
	{
		shape.Accept(painter);
	}
}
