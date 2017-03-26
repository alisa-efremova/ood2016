#pragma once

#include "targetver.h"

#include <stdio.h>
#include <tchar.h>

#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <deque>
#include <memory>
#include <functional>
#include <sstream>
#include <cassert>
#include <cctype>
#include <boost/range/algorithm/find_if.hpp>
#include <boost/scope_exit.hpp>
#include <boost/optional.hpp>
#include <boost/none.hpp>

///=======================================
#define BOOST_TEST_MODULE WeatherStationTests
#define BOOST_TEST_INCLUDED
#pragma warning (disable:4702 4913 4535)
#include <boost/test/unit_test.hpp>
///=======================================