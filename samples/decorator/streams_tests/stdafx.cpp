// stdafx.cpp : source file that includes just the standard includes
// streams_tests.pch will be the pre-compiled header
// stdafx.obj will contain the pre-compiled type information

#include "stdafx.h"

// TODO: reference any additional headers you need in STDAFX.H
// and not in this file




namespace std
{

std::ostream& operator<<(std::ostream& stream, std::vector<uint8_t> const& data)
{
	for (auto& v : data)
	{
		stream << v << ' ';
	}
	return stream;
}

}
