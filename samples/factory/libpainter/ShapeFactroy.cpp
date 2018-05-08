#include "stdafx.h"
#include "ShapeFactroy.h"
#include "Shape.h"
#include "Rectangle.h"

using namespace std;
using TokenIt = vector<std::string>::const_iterator;

namespace
{

IShapeUniquePtr CreateRect(TokenIt start, TokenIt end)
{
	return std::make_unique<Shape>();
}

}

IShapeUniquePtr ShapeFactroy::CreateShape(const std::string & description)
{
	istringstream iss(description);
	vector<std::string> tokens{ istream_iterator<string>{iss}, istream_iterator<string>{} };
// 
// 	try
// 	{
// 		auto const& shapeType = tokens.front();
// 		if (shapeType == "rect")
// 		{
// 			return CreateRect(tokens.begin() + 1, tokens.end());
// 		}
// 	}
// 	catch (...)
// 	{
// 		// invalid shape
// 	}
 	return nullptr;
}
