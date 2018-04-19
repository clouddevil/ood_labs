#pragma once

#include <windows.h>

class TempFilename
	: boost::noncopyable
{
public:
	TempFilename(std::string const& fn)
		: m_name(fn)
	{
	}

	std::string name() const
	{
		return m_name;
	}

	~TempFilename()
	{	
		::DeleteFileA(m_name.c_str());
		//boost::filesystem::remove(m_name);
	}

private:
	std::string m_name;
};
