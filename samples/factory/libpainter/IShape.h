#pragma once

#include "IGroup.h"
#include "Point.h"
#include "IShapeVisitor.h"
#include "Style.h"

class IShape
{
public:	
	virtual ~IShape() = default;

	virtual void Accept(IShapeVisitor& visitor) = 0;

	virtual IGroup* GetGroup() = 0;

	virtual Rect GetFrame() const = 0;
	virtual void SetFrame(Rect const& rc) = 0;

	virtual LineStylePtr GetLineStyle() const = 0;
	virtual void SetLineStyle(LineStylePtr const& style) = 0;
	
	virtual FillStylePtr GetFillStyle() const = 0;
	virtual void SetFillStyle(FillStylePtr const& style) = 0;	
};

using IShapeUniquePtr = std::unique_ptr<IShape>;