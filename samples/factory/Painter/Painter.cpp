// Painter.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "../libpainter/Designer.h"
#include "../libpainter/ShapeFactroy.h"
#include "../libpainter/PictureDraft.h"

using namespace std;

int main()
{
	ShapeFactroy shapeFactory;
	Designer designer(shapeFactory);

	std::istringstream s(" ");
	//std::istringstream s("rect 0 0 100 100");

	auto draft = designer.CreateDraft(s);

	//auto draft = designer.CreateDraft(std::cin);


// 	SvgCanvas svg;
// 	svg.BeginDraw();
// 	{
// 		SvgSerializer serializer(svg);

// 		for (auto & shape : draft)
// 		{
// 			shape.Accept(painter);
// 		}
// 	}
// 	svg.EndDraw();
	
	return 0;
}

