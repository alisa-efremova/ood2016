#pragma once

#include <boost/noncopyable.hpp>
#include <boost/signals2.hpp>

namespace signals = boost::signals2;

class IWeatherData
{
public:
	using WeatherDataSignal = signals::signal<void(const class CWeatherData *)>;
	virtual signals::connection DoOnChange(const WeatherDataSignal::slot_type & slot) = 0;
	virtual ~IWeatherData() = default;
};

class CWeatherData : public IWeatherData
{
public:
	void SetMeasurements(double temp, double humidity, double pressure)
	{
		m_humidity = humidity;
		m_temperature = temp;
		m_pressure = pressure;

		m_changeSignal(this);
	}

	virtual signals::connection DoOnChange(const WeatherDataSignal::slot_type & slot) override
	{
		return m_changeSignal.connect(slot);
	}

	double GetTemperature()const
	{
		return m_temperature;
	}

	double GetHumidity()const
	{
		return m_humidity;
	}

	double GetPressure()const
	{
		return m_pressure;
	}

private:
	double m_temperature = 59.0;
	double m_humidity = 0.0;
	double m_pressure = 760.0;
	WeatherDataSignal m_changeSignal;
};