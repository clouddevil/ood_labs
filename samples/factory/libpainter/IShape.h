#pragma once

#include "IShapeVisitor.h"
#include "CommonTypes.h"
#include "IOutlineStyle.h"
#include "IFillStyle.h"

class IGroup;

class IShape
{
public:	
	virtual ~IShape() = default;

	virtual void Accept(IShapeVisitor& visitor) const = 0;

	virtual IGroup* GetGroup() = 0;

	virtual RectD GetFrame() const = 0;
	virtual void SetFrame(RectD const& rc) = 0;

	virtual IOutlineStyle& GetOutlineStyle() = 0;
	virtual IOutlineStyle const& GetOutlineStyle() const = 0;
	
	virtual IFillStyle& GetFillStyle() = 0;
	virtual IFillStyle const& GetFillStyle() const = 0;
};

using IShapeUniquePtr = std::unique_ptr<IShape>;