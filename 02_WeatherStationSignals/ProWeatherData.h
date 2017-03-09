#pragma once
#include "WeatherStationLocation.h"

namespace signals = boost::signals2;

class CProWeatherData 
{
public:
	using WeatherSignal = signals::signal<void(double)>;

	void SetMeasurements(double temp, double humidity, double pressure, double windSpeed, double windDirection);
	signals::connection DoOnTemperatureChange(const WeatherSignal::slot_type & slot);
	signals::connection DoOnHumidityChange(const WeatherSignal::slot_type & slot);
	signals::connection DoOnPressureChange(const WeatherSignal::slot_type & slot);
	signals::connection DoOnWindSpeedChange(const WeatherSignal::slot_type & slot);
	signals::connection DoOnWindDirectionChange(const WeatherSignal::slot_type & slot);
	
	double GetTemperature()const;
	double GetHumidity()const;
	double GetPressure()const;
	double GetWindSpeed()const;
	double GetWindDirection()const;
	WeatherStationLocation GetLocation()const;

private:
	double m_temperature = 0.0;
	double m_humidity = 0.0;
	double m_pressure = 760.0;
	double m_windSpeed = 0.0;
	double m_windDirection = 0;
	WeatherStationLocation m_location = WeatherStationLocation::OUT;
	WeatherSignal m_temperatureChangeSignal;
	WeatherSignal m_humidityChangeSignal;
	WeatherSignal m_pressureChangeSignal;
	WeatherSignal m_windSpeedChangeSignal;
	WeatherSignal m_windDirectionChangeSignal;
};