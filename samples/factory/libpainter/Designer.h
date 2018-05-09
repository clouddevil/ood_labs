#pragma once

class PictureDraft;
class IShapeFactory;

class Designer
{
public:
	Designer(IShapeFactory & factory);
	
	PictureDraft CreateDraft(std::istream & inputData);

private:
	void TryAddShape(PictureDraft& draft, std::string const& shapeDescr);

private:
	IShapeFactory & m_factory;
};

