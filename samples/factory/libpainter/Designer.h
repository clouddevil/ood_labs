#pragma once

class PictureDraft;
class IShapeFactory;

class Designer
{
public:
	Designer(IShapeFactory & factory);
	
	PictureDraft CreateDraft(std::istream & inputData);
private:
	IShapeFactory & m_factory;
};

