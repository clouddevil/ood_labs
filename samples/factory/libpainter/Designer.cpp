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
		draft.AddShape(m_factory.CreateShape(line));
	}
	return draft;
}
