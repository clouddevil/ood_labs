#pragma once


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
		//boost::filesystem::remove(m_name);
	}

private:
	std::string m_name;
};
