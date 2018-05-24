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

	auto rc = shape.GetRect();

	auto right = rc.left + rc.width;
	auto bottom = rc.top + rc.height;

	std::vector<PointD> v;
	v.push_back({rc.left, rc.top});
	v.push_back({ right, rc.top });
	v.push_back({ right, bottom });
	v.push_back({ rc.left, bottom });
	m_canvas.DrawPolygon(v);
}

void DraftPainter::Visit(shape::Triangle const& shape)
{
	SetCanvasShapeStyle(shape);

	std::vector<PointD> v;
	v.push_back(shape.GetVertex1());
	v.push_back(shape.GetVertex2());
	v.push_back(shape.GetVertex3());
	m_canvas.DrawPolygon(v);
}

void DraftPainter::Visit(shape::Ellipse const& shape)
{
	SetCanvasShapeStyle(shape);

	m_canvas.DrawEllipse(shape.GetCenter(), shape.GetSize());
}

void DraftPainter::SetCanvasShapeStyle(IShape const& shape)
{
	auto& fill = shape.GetFillStyle();
	auto& outline = shape.GetOutlineStyle();

	CanvasDrawingState state;
	state.outlineThin = outline.GetThickness();
	state.outlineColor = outline.GetColor();
	state.fillColor = fill.GetColor();	
	m_canvas.SetDrawingState(state);
}

void PaintDraft(IPictureDraft const& draft, ICanvas& canvas)
{	
	DraftPainter painter(canvas);
	for (auto const& shape : draft)
	{
		shape.Accept(painter);
	}
}
