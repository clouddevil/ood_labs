#include "stdafx.h"
#include "Designer.h"
#include "PictureDraft.h"
#include "IShapeFactory.h"


using namespace std;

Designer::Designer(IShapeFactory & factory)
	:m_factory(factory)
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
		std::cout << "Error: " << e.what() << std::endl;
	}
}
