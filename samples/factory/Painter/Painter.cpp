// Painter.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "../libpainter/Designer.h"
#include "../libpainter/ShapeFactroy.h"
#include "../libpainter/PictureDraft.h"
#include "../libpainter/SvgCanvas.h"
#include "../libpainter/DraftPainter.h"

using namespace std;

void DrawStr(std::string const& str, Designer& designer, ICanvas& canvas)
{
	std::istringstream s(str);
	auto draft = designer.CreateDraft(s);
	PaintDraft(draft, canvas);
}

void DrawCar(Designer& designer, ICanvas& canvas)
{
	std::ostringstream buffer;
	buffer << "rect 30 40 100 100" << std::endl;
	buffer << "triangle 75 75 200 100 140 140" << std::endl;
	buffer << "ellipse 75 75 200 100 " << std::endl;

	DrawStr(buffer.str(), designer, canvas);
}

void DrawSun(Designer& designer, ICanvas& canvas)
{
	std::ostringstream buffer;
	buffer << "rect 0 0 100 100" << std::endl;

	DrawStr(buffer.str(), designer, canvas);
}

int main()
{
	try
	{
		ShapeFactroy shapeFactory;
		Designer designer(shapeFactory);

		SvgCanvas canvas("draft.svg");
		canvas.BeginDraw(1280, 1024);

#if 0
		auto draft = designer.CreateDraft(std::cin);
		PaintDraft(draft, canvas);
#endif

#if 1
		//DrawSun(designer, canvas);
		DrawCar(designer, canvas);
#endif

		canvas.EndDraw();
	}
	catch (std::exception const& e)
	{
		std::cout << e.what() << std::endl;
	}

	return 0;
}

