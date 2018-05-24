// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#include "targetver.h"

#include <wtypes.h>
#include <vector>
#include <istream>
#include <iostream>
#include <iosfwd>
#include <sstream>
#include <iterator>
#include <memory>
#include <string>
#include <functional>


#define BOOST_TEST_INCLUDED
#pragma warning (push, 3)
#pragma warning (disable:4456 4702)
#include <boost/test/unit_test.hpp>
#pragma warning (pop)


#include <boost/optional.hpp>
#include <boost/optional/optional_io.hpp>
#include <boost/iterator/indirect_iterator.hpp>
#include <boost/range/algorithm/copy.hpp>
#include <boost/algorithm/cxx11/all_of.hpp>




