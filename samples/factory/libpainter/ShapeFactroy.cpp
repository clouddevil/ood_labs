#include "stdafx.h"
#include "ShapeFactroy.h"
#include "Shape.h"

using namespace std;

IShapeUniquePtr ShapeFactroy::CreateShape(const std::string & description)
{
	istringstream iss(description);
	vector<std::string> tokens{ istream_iterator<string>{iss}, istream_iterator<string>{} };



	return nullptr;
}
