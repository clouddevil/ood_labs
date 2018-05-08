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
	CDesigner designer(shapeFactory);

	auto draft = designer.CreateDraft(std::cin);


 	SvgCanvas svg;
 	svg.BeginDraw();
	{
		SvgSerializer serializer(svg);

		for (auto & shape : draft)
		{
			shape->Draw();
		}
	}
	svg.EndDraw();
	
	return 0;
}

