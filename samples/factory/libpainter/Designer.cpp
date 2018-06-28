#include "stdafx.h"
#include "Designer.h"
#include "PictureDraft.h"
#include "IShapeFactory.h"
#include "IGroup.h"


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
		if (line == "+group")
		{
			draft.AddShape(CreateDraft(inputData).MoveAsShape());
		}
		else if (line == "-group")
		{
			break;
		}
		else
		{
			TryParseShape(draft, line);
		}
	}

	return draft;
}

void Designer::TryParseShape(PictureDraft& draft, std::string const& shapeDescr)
{
	try
	{
		if (auto shape = m_factory.CreateShape(shapeDescr))
		{
			draft.AddShape(move(shape));
		}
	}
	catch (std::exception const& e)
	{
		m_errorCallback(e);
	}
}

