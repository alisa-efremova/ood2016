// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#include "targetver.h"

#include <stdio.h>
#include <tchar.h>

#include <iostream>

///=======================================
#define BOOST_TEST_MODULE WeatherStationTests
#define BOOST_TEST_INCLUDED
#pragma warning (disable:4702 4913 4535)
#include <boost/test/unit_test.hpp>
///=======================================
