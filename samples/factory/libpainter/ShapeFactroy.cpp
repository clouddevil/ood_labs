#include "stdafx.h"
#include "ShapeFactroy.h"
#include "Shapes.h"

using namespace std;
using TokenIt = vector<std::string>::const_iterator;

namespace
{

IShapeUniquePtr CreateRect(TokenIt start, TokenIt end)
{
	return std::make_unique<shape::Rectangle>();
}

IShapeUniquePtr CreateTriangle(TokenIt start, TokenIt end)
{
	return std::make_unique<shape::Triangle>();
}

IShapeUniquePtr CreateEllipse(TokenIt start, TokenIt end)
{
	return std::make_unique<shape::Ellipse>();
}

}

IShapeUniquePtr ShapeFactroy::CreateShape(const std::string & description)
{
	istringstream iss(description);
	vector<std::string> tokens{ istream_iterator<string>{iss}, istream_iterator<string>{} };

	if (tokens.empty())
	{
		return nullptr;
	}


	auto const& shapeType = tokens.front();
	if (shapeType == "rect")
	{
		return CreateRect(tokens.begin() + 1, tokens.end());
	}
	if (shapeType == "triangle")
	{
		return CreateTriangle(tokens.begin() + 1, tokens.end());
	}
	if (shapeType == "ellipse")
	{
		return CreateEllipse(tokens.begin() + 1, tokens.end());
	}
	
	throw std::runtime_error("Unknown shape description");
}
