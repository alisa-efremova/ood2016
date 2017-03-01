#pragma once
#include "IWeatherData.h"

class CWeatherData : public IWeatherData<CWeatherData>
{
public:
	void SetMeasurements(double temp, double humidity, double pressure);
	virtual signals::connection DoOnChange(const signals::signal<void(const CWeatherData *)>::slot_type & slot) override;
	double GetTemperature()const;
	double GetHumidity()const;
	double GetPressure()const;

private:
	double m_temperature = 59.0;
	double m_humidity = 0.0;
	double m_pressure = 760.0;
	signals::signal<void(const CWeatherData *)>	m_changeSignal;
};
