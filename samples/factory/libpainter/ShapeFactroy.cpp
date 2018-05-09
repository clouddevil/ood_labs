#include "stdafx.h"
#include "ShapeFactroy.h"
#include "Shapes.h"

using namespace std;
using TokenIt = vector<std::string>::const_iterator;

namespace
{

int ParseInt(TokenIt& start, TokenIt end)
{
	std::advance(start, 1);
	if (start != end)
	{	
		return std::atoi(start->c_str());
	}
	throw std::runtime_error("Not enough shape parameters");
}

PointD ParsePoint(TokenIt& start, TokenIt end)
{
	auto x = ParseInt(start, end);
	auto y = ParseInt(start, end);
	return { x, y };
}

IShapeUniquePtr CreateRect(TokenIt start, TokenIt end)
{	
	auto v1 = ParsePoint(start, end);
	auto v2 = ParsePoint(start, end);
	return std::make_unique<shape::Rectangle>(RectD{v1.x, v1.y, v2.x, v2.y});
}

IShapeUniquePtr CreateTriangle(TokenIt start, TokenIt end)
{
	auto v1 = ParsePoint(start, end);
	auto v2 = ParsePoint(start, end);
	auto v3 = ParsePoint(start, end);
	return std::make_unique<shape::Triangle>(v1, v2, v3);
}

IShapeUniquePtr CreateEllipse(TokenIt start, TokenIt end)
{
	auto v1 = ParsePoint(start, end);
	auto v2 = ParsePoint(start, end);
	return std::make_unique<shape::Ellipse>(v1, v2);
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
		return CreateRect(tokens.begin(), tokens.end());
	}
	if (shapeType == "triangle")
	{
		return CreateTriangle(tokens.begin(), tokens.end());
	}
	if (shapeType == "ellipse")
	{
		return CreateEllipse(tokens.begin(), tokens.end());
	}
	
	throw std::runtime_error("Unknown shape description");
}
