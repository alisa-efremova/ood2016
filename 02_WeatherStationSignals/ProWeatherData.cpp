#include "stdafx.h"
#include "ProWeatherData.h"

void CProWeatherData::SetMeasurements(double temp, double humidity, double pressure, double windSpeed, double windDirection)
{
	if (m_temperature != temp)
	{
		m_temperature = temp;
		m_temperatureChangeSignal(m_temperature);
	}

	if (m_humidity != humidity)
	{
		m_humidity = humidity;
		m_humidityChangeSignal(m_humidity);
	}

	if (m_pressure != pressure)
	{
		m_pressure = pressure;
		m_pressureChangeSignal(m_pressure);
	}

	if (m_windSpeed != windSpeed)
	{
		m_windSpeed = windSpeed;
		m_windSpeedChangeSignal(m_windSpeed);
	}

	if (m_windDirection != windDirection)
	{
		m_windDirection = windDirection;
		m_windDirectionChangeSignal(m_windDirection);
	}
}

signals::connection CProWeatherData::DoOnTemperatureChange(const WeatherSignal::slot_type & slot)
{
	return m_temperatureChangeSignal.connect(slot);
}

signals::connection CProWeatherData::DoOnHumidityChange(const WeatherSignal::slot_type & slot)
{
	return m_humidityChangeSignal.connect(slot);
}

signals::connection CProWeatherData::DoOnPressureChange(const WeatherSignal::slot_type & slot)
{
	return m_pressureChangeSignal.connect(slot);
}

signals::connection CProWeatherData::DoOnWindSpeedChange(const WeatherSignal::slot_type & slot)
{
	return m_windSpeedChangeSignal.connect(slot);
}

signals::connection CProWeatherData::DoOnWindDirectionChange(const WeatherSignal::slot_type & slot)
{
	return m_windDirectionChangeSignal.connect(slot);
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