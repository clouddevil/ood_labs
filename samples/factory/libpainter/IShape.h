#pragma once

class IShapeVisitor
{
public:
	virtual ~IShapeVisitor() = default;
};

class IShape
{
public:	
	virtual ~IShape() = default;

	virtual void Accept(IShapeVisitor& visitor) = 0;
};

using IShapeUniquePtr = std::unique_ptr<IShape>;