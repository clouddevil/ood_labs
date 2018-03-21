// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#include "targetver.h"

#include <stdio.h>
#include <tchar.h>
#include <algorithm>
#include <functional>


#define BOOST_TEST_MODULE WeatherStationTests

#pragma warning (push, 3)
#pragma warning (disable:4456 4702)
#include <boost/test/unit_test.hpp>
#pragma warning (pop)


#define _USE_MATH_DEFINES
#include <cmath>
#include <math.h>

namespace std
{

std::ostream& operator<<(std::ostream& stream, std::vector<int> const& vec);

}
