#pragma once

class PictureDraft;
class IShapeFactory;

class Designer
{
public:
	using ErrorCallback = std::function<void(std::exception const&)>;
	Designer(IShapeFactory & factory, ErrorCallback const& errorCallback);
	
	PictureDraft CreateDraft(std::istream & inputData);

private:
	void TryAddShape(PictureDraft& draft, std::string const& shapeDescr);

private:
	IShapeFactory & m_factory;
	ErrorCallback m_errorCallback;
};

