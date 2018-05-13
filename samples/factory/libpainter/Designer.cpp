#include "stdafx.h"
#include "Designer.h"
#include "PictureDraft.h"
#include "IShapeFactory.h"


using namespace std;

Designer::Designer(IShapeFactory & factory, ErrorCallback const& errorCallback)
	: m_errorCallback(errorCallback)
	, m_factory(factory)
{
}

PictureDraft Designer::CreateDraft(std::istream & inputData)
{
	PictureDraft draft;
	string line;
	while (getline(inputData, line))
	{
		TryAddShape(draft, line);
	}
	return draft;
}

void Designer::TryAddShape(PictureDraft& draft, std::string const& shapeDescr)
{
	try
	{
		draft.AddShape(m_factory.CreateShape(shapeDescr));
	}
	catch (std::exception const& e)
	{
		m_errorCallback(e);
	}
}
