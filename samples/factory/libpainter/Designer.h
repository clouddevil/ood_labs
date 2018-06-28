#pragma once
#include "IShape.h"
#include "ShapeStorage.h"

class PictureDraft;
class IShapeFactory;

class Designer
{
public:
	using ErrorCallback = std::function<void(std::exception const&)>;
	Designer(IShapeFactory & factory, ErrorCallback const& errorCallback);
	
	PictureDraft CreateDraft(std::istream & inputData);

private:
	//void PopGroupShape(PictureDraft& shape);
	//void InsertShape(PictureDraft& draft, IShapeUniquePtr&& shape);
	void TryParseShape(PictureDraft& draft, std::string const& shapeDescr);


private:
	IShapeFactory & m_factory;
	ShapeStorage m_groups;
	ErrorCallback m_errorCallback;	
};

