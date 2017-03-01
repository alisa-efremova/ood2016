#pragma once
#include "IWeatherData.h"
#include "WeatherStationLocation.h"

class CWeatherData : public IWeatherData<CWeatherData>
{
public:
	void SetMeasurements(double temp, double humidity, double pressure);
	virtual signals::connection DoOnChange(const signals::signal<void(const CWeatherData *)>::slot_type & slot) override;
	double GetTemperature()const;
	double GetHumidity()const;
	double GetPressure()const;
	WeatherStationLocation GetLocation()const;

private:
	double m_temperature = 59.0;
	double m_humidity = 0.0;
	double m_pressure = 760.0;
	WeatherStationLocation m_location = WeatherStationLocation::IN;
	signals::signal<void(const CWeatherData *)>	m_changeSignal;
};
