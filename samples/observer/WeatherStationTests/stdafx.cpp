// stdafx.cpp : source file that includes just the standard includes
// WeatherStationTests.pch will be the pre-compiled header
// stdafx.obj will contain the pre-compiled type information

#include "stdafx.h"

// TODO: reference any additional headers you need in STDAFX.H
// and not in this file

std::ostream& std::operator<<(ostream& stream, vector<int> const& vec)
{
	for (auto&& v : vec)
	{
		stream << std::to_string(v) << " ";
	}
	return stream;
}
