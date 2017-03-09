#pragma once
#include "WeatherStationLocation.h"

namespace signals = boost::signals2;

class CWeatherData
{
public:
	using WeatherSignal = signals::signal<void(double)>;

	void SetMeasurements(double temp, double humidity, double pressure);
	signals::connection DoOnTemperatureChange(const WeatherSignal::slot_type & slot);
	signals::connection DoOnHumidityChange(const WeatherSignal::slot_type & slot);
	signals::connection DoOnPressureChange(const WeatherSignal::slot_type & slot);
	double GetTemperature()const;
	double GetHumidity()const;
	double GetPressure()const;
	WeatherStationLocation GetLocation()const;

private:
	double m_temperature = 59.0;
	double m_humidity = 0.0;
	double m_pressure = 760.0;
	WeatherStationLocation m_location = WeatherStationLocation::IN;
	WeatherSignal m_temperatureChangeSignal;
	WeatherSignal m_humidityChangeSignal;
	WeatherSignal m_pressureChangeSignal;
};
