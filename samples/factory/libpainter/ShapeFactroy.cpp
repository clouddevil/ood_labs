#include "stdafx.h"
#include "ShapeFactroy.h"
#include "Shapes.h"
#include <boost\lexical_cast.hpp>
#include "Group.h"

using namespace std;
using TokenIt = vector<std::string>::const_iterator;

namespace
{

const std::string NoStyleToken = "-";

uint32_t ParseColor(TokenIt const& start)
{
	//return std::atoi(start->c_str());
	return strtoul(start->c_str(), nullptr, 16);
}

int ParseInt(TokenIt const& start)
{
	//return std::atoi(start->c_str());
	return boost::lexical_cast<int>(start->c_str());
}

void AdvanceAndCheck(TokenIt& start, TokenIt end)
{
	std::advance(start, 1);
	if (start == end)
	{
		throw std::runtime_error("Not enough shape parameters");
	}	
}

int ParseIntAndAdvance(TokenIt& start, TokenIt end)
{
	AdvanceAndCheck(start, end);
	return std::atoi(start->c_str());	
}

PointD ParsePoint(TokenIt& start, TokenIt end)
{
	auto x = ParseIntAndAdvance(start, end);
	auto y = ParseIntAndAdvance(start, end);
	return { x, y };
}

IShapeUniquePtr ParseShapeStyle(IShapeUniquePtr&& shape, TokenIt start, TokenIt end)
{
	/*
	AdvanceAndCheck(start, end);	
	if (*start != NoStyleToken)
	{
		auto style = std::make_shared<FillStyle>();
		style->fillColor = ParseColor(start);
		shape->SetFillStyle(style);
	}

	AdvanceAndCheck(start, end);
	if (*start != NoStyleToken)
	{
		auto style = std::make_shared<LineStyle>();
		style->fillColor = ParseColor(start);
		
		std::advance(start, 1);
		if (start != end)
		{
			style->thin = 1.0f * ParseInt(start);
		}
		shape->SetLineStyle(style);
	}	
	*/
	return move(shape);
}

IShapeUniquePtr CreateRect(TokenIt start, TokenIt end)
{	
	auto v1 = ParsePoint(start, end);
	auto v2 = ParsePoint(start, end);
	auto shape = std::make_unique<shape::Rectangle>(RectD{ v1.x, v1.y, v2.x, v2.y });
	return ParseShapeStyle(std::move(shape), start, end);
}

IShapeUniquePtr CreateTriangle(TokenIt start, TokenIt end)
{
	auto v1 = ParsePoint(start, end);
	auto v2 = ParsePoint(start, end);
	auto v3 = ParsePoint(start, end);
	auto shape = std::make_unique<shape::Triangle>(v1, v2, v3);
	return ParseShapeStyle(std::move(shape), start, end);
}

IShapeUniquePtr CreateEllipse(TokenIt start, TokenIt end)
{
	auto v1 = ParsePoint(start, end);
	auto v2 = ParsePoint(start, end);
	auto shape = std::make_unique<shape::Ellipse>(v1, v2);
	return ParseShapeStyle(std::move(shape), start, end);
}

}

IShapeUniquePtr ShapeFactroy::CreateShape(const std::string & description)
{
	Group g;

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
	if (shapeType == "+group")
	{
		//return std::make_unique<Group>();
	}	
	if (shapeType == "-group")
	{
		// ok
		return nullptr;
	}
	throw std::runtime_error("Unknown shape description");
}
