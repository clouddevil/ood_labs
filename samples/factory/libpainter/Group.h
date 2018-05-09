#pragma once
#include "IGroup.h"

class Group
	: public IGroup
{
public:
	Group();
	~Group();

	virtual void Accept(IShapeVisitor& visitor) const override;


	virtual IGroup* GetGroup() override;


	virtual RectD GetFrame() const override;


	virtual void SetFrame(RectD const& rc) override;


	virtual LineStylePtr GetLineStyle() const override;


	virtual void SetLineStyle(LineStylePtr const& style) override;


	virtual FillStylePtr GetFillStyle() const override;


	virtual void SetFillStyle(FillStylePtr const& style) override;

};

