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
		TryAddShape(draft, line);
	}

	while (!m_groups.empty())
	{
		PopGroupShape(draft);
	}

	return draft;
}

void Designer::PopGroupShape(PictureDraft& draft)
{
	draft.AddShape(GetLastShape());
}

void Designer::InsertShape(PictureDraft& draft, IShapeUniquePtr&& shape)
{
	if (m_groups.empty())
	{
		draft.AddShape(move(shape));
	}
	else
	{
		auto& last = m_groups.back();
		if (auto g = last->GetGroup())
		{
			g->InsertShape(move(shape));
		}
		else
		{
			throw std::runtime_error("Invalid shape type");
		}
	}
}

void Designer::TryAddShape(PictureDraft& draft, std::string const& shapeDescr)
{
	try
	{
		if (shapeDescr == "-group")
		{
			PopGroupShape(draft);
		}
		else if (auto shape = m_factory.CreateShape(shapeDescr))
		{
			if (auto g = shape->GetGroup())
			{
				m_groups.emplace_back(move(shape));
			}
			else
			{
				InsertShape(draft, move(shape));			
			}
		}
	}
	catch (std::exception const& e)
	{
		m_errorCallback(e);
	}
}

IShapeUniquePtr Designer::GetLastShape()
{
	if (m_groups.empty())
	{
		throw std::runtime_error("No groups");
	}

	auto last = move(m_groups.back());
	m_groups.pop_back();
	return last;
}
