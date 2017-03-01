#include "stdafx.h"
#include "ProWeatherData.h"

void CProWeatherData::SetMeasurements(double temp, double humidity, double pressure, double windSpeed, double windDirection)
{
	m_humidity = humidity;
	m_temperature = temp;
	m_pressure = pressure;
	m_windSpeed = windSpeed;
	m_windDirection = windDirection;

	m_changeSignal(this);
}

signals::connection CProWeatherData::DoOnChange(const signals::signal<void(const CProWeatherData *)>::slot_type & slot)
{
	return m_changeSignal.connect(slot);
}

double CProWeatherData::GetTemperature() const
{
	return m_temperature;
}

double CProWeatherData::GetHumidity() const
{
	return m_humidity;
}

double CProWeatherData::GetPressure() const
{
	return m_pressure;
}

double CProWeatherData::GetWindSpeed() const
{
	return m_windSpeed;
}

double CProWeatherData::GetWindDirection() const
{
	return m_windDirection;
}

WeatherStationLocation CProWeatherData::GetLocation()const
{
	return m_location;
}