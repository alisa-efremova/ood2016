#pragma once
#include <boost/noncopyable.hpp>
#include <boost/signals2.hpp>

namespace signals = boost::signals2;

template <class T>
class IWeatherData
{
public:
	virtual signals::connection DoOnChange(const typename signals::signal<void(const T *)>::slot_type & slot) = 0;
	virtual ~IWeatherData() = default;
};