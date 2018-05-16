#pragma once

#include "../libpainter/Shape.h"
#include "../libpainter/IShapeFactory.h"

namespace
{

using namespace std;

class MockShape : public IShape
{
public:
	MockShape() = default;

	MockShape(const string& descr)		
		: descr(descr)
	{
	}
	string descr;

	void Accept(IShapeVisitor& /*visitor*/) const override
	{
		throw std::logic_error("The method or operation is not implemented.");
	}

	IGroup* GetGroup() override
	{
		return nullptr;
	}

	RectD GetFrame() const override
	{
		throw std::logic_error("The method or operation is not implemented.");
	}

	void SetFrame(RectD const& /*rc*/) override
	{
		throw std::logic_error("The method or operation is not implemented.");
	}

	LineStylePtr GetLineStyle() const override
	{
		throw std::logic_error("The method or operation is not implemented.");
	}

	void SetLineStyle(LineStylePtr const& /*style*/) override
	{
		throw std::logic_error("The method or operation is not implemented.");
	}

	FillStylePtr GetFillStyle() const override
	{
		throw std::logic_error("The method or operation is not implemented.");
	}

	void SetFillStyle(FillStylePtr const& /*style*/) override
	{
		throw std::logic_error("The method or operation is not implemented.");
	}
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
