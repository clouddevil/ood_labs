// Painter.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "../libpainter/Designer.h"
#include "../libpainter/ShapeFactroy.h"
#include "../libpainter/PictureDraft.h"
#include "../libpainter/SvgCanvas.h"
#include "../libpainter/DraftPainter.h"

using namespace std;

void Help()
{
	std::cout << "Available shapes: " << std::endl;
	std::cout << "rect <pt> <size> <style>" << std::endl;
	std::cout << "ellipse <pt> <size> <style>" << std::endl;
	std::cout << "triangle <pt> <pt> <pt> <style>" << std::endl;
	
	std::cout << "<pt> := int int" << std::endl;
	std::cout << "<size> := int int" << std::endl;

	std::cout << "<style> := <color?> <color?> <thin?>" << std::endl;	
	std::cout << "<color?> := int32 | '-'" << std::endl;
	std::cout << "<thin?> := int | none" << std::endl;
	std::cout << std::endl;
}

void DrawStr(std::string const& str, Designer& designer, ICanvas& canvas)
{
	std::istringstream s(str);
	auto draft = designer.CreateDraft(s);
	PaintDraft(draft, canvas);
}

void DrawCar(Designer& designer, ICanvas& canvas)
{
	std::ostringstream buffer;
	buffer << "rect 30 40 100 100 0xFF - 1  " << std::endl;
	buffer << "triangle 75 75 200 100 140 140 0xFFFFFF 0xFF 1" << std::endl;
	//buffer << "ellipse 75 75 200 100 s " << std::endl;
	buffer << "ellipse 600 600 50 50 0xFF0000 - " << std::endl;

	DrawStr(buffer.str(), designer, canvas);
}

void DrawSun(Designer& designer, ICanvas& canvas)
{
	std::ostringstream buffer;
	buffer << "ellipse 800 0 150 90 0xFFFF00 0x99FFFF00 10" << std::endl;	
	buffer << "triangle 775 75 200 100 140 140 0xFFFF00 0x99FFFF00 1" << std::endl;
	//buffer << "ellipse 75 75 200 100 s " << std::endl;
	//buffer << "ellipse 600 600 50 50 0xFF0000 - " << std::endl;


	DrawStr(buffer.str(), designer, canvas);
}

void ErrorHandler(std::exception const& e)
{
	std::cout << "Error: " << e.what() << std::endl;

	Help();
}

int main()
{
	try
	{
		ShapeFactroy shapeFactory;
		Designer designer(shapeFactory, std::bind(ErrorHandler, std::placeholders::_1));

		SvgCanvas canvas("draft.svg");
		canvas.BeginDraw(800, 600);

#if 0
		auto draft = designer.CreateDraft(std::cin);
		PaintDraft(draft, canvas);
#endif

#if 1
		DrawSun(designer, canvas);
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

