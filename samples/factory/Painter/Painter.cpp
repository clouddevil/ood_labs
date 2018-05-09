// Painter.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "../libpainter/Designer.h"
#include "../libpainter/ShapeFactroy.h"
#include "../libpainter/PictureDraft.h"
#include "../libpainter/SvgCanvas.h"
#include "../libpainter/DraftPainter.h"

using namespace std;

void DrawCar(Designer& designer, ICanvas& canvas)
{
	std::istringstream s("rect 0 0 100 100");
	auto draft = designer.CreateDraft(s);
	PaintDraft(draft, canvas);
}

void DrawSun(Designer& designer, ICanvas& canvas)
{
	std::istringstream s("rect 0 0 100 100");
	auto draft = designer.CreateDraft(s);
	PaintDraft(draft, canvas);
}

int main()
{
	try
	{
		ShapeFactroy shapeFactory;
		Designer designer(shapeFactory);

		auto draft = designer.CreateDraft(std::cin);
		SvgCanvas canvas("draft.svg");
		canvas.BeginDraw(1280, 1024);

		PaintDraft(draft, canvas);

#if 1
		//DrawSun(designer, canvas);
		//DrawCar(designer, canvas);
#endif

		canvas.EndDraw();
	}
	catch (std::exception const& e)
	{
		std::cout << e.what() << std::endl;
	}

	return 0;
}

