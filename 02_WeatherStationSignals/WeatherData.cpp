#include "stdafx.h"
#include "WeatherData.h"

void CWeatherData::SetMeasurements(double temp, double humidity, double pressure)
{
	m_humidity = humidity;
	m_temperature = temp;
	m_pressure = pressure;

	m_changeSignal(this);
}

signals::connection CWeatherData::DoOnChange(const signals::signal<void(const CWeatherData *)>::slot_type & slot)
{
	return m_changeSignal.connect(slot);
}

double CWeatherData::GetTemperature()const
{
	return m_temperature;
}

double CWeatherData::GetHumidity()const
{
	return m_humidity;
}

double CWeatherData::GetPressure()const
{
	return m_pressure;
}
