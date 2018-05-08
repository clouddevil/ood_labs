#pragma once


class CPictureDraft;
class IShapeFactory;

class CDesigner
{
public:
	CDesigner(IShapeFactory & factory);
	
	CPictureDraft CreateDraft(std::istream & inputData);
private:
	IShapeFactory & m_factory;
};

