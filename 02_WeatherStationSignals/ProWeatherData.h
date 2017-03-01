#pragma once
#include "IWeatherData.h"

class CProWeatherData : public IWeatherData<CProWeatherData>
{
public:
	void SetMeasurements(double temp, double humidity, double pressure, double windSpeed, double windDirection);
	virtual signals::connection DoOnChange(const signals::signal<void(const CProWeatherData *)>::slot_type & slot) override;
	
	double GetTemperature()const;
	double GetHumidity()const;
	double GetPressure()const;
	double GetWindSpeed()const;
	double GetWindDirection()const;
private:
	double m_temperature = 0.0;
	double m_humidity = 0.0;
	double m_pressure = 760.0;
	double m_windSpeed = 0.0;
	double m_windDirection = 0;
	signals::signal<void(const CProWeatherData *)> m_changeSignal;
};