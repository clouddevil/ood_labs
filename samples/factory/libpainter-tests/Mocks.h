#pragma once

#include "../libpainter/Shape.h"
#include "../libpainter/IShapeFactory.h"

namespace
{

using namespace std;

class MockShape : public Shape
{
public:
	MockShape() = default;

	MockShape(const string& descr)		
		: descr(descr)
	{
	}
	string descr;
};


struct MockShapeFactory : IShapeFactory
{
	vector<string> shapeDescriptions;

	IShapeUniquePtr CreateShape(const std::string & description) override
	{		
		shapeDescriptions.push_back(description);
		return make_unique<MockShape>(description);
	}
};


}
