#pragma once
#include "IShapeVisitor.h"
#include "IPainter.h"
#include "IShape.h"

class DraftPainter final	
	: public IShapeVisitor
{
public:
	DraftPainter(ICanvas& canvas);

	void Visit(shape::Rectangle const& rect) override;
	void Visit(shape::Triangle const& rect) override;
	void Visit(shape::Ellipse const& rect) override;

private:
	void SetCanvasShapeStyle(IShape const& shape);

private:
	ICanvas& m_canvas;
};

void PaintDraft(IPictureDraft const& draft, ICanvas& canvas);