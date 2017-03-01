#include "stdafx.h"
#include "ProWeatherData.h"
#include "WeatherInfoType.h"

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

WeatherStationLocation CProWeatherData::GetLocation() const
{
	return m_location;
}

void CProWeatherData::MeasurementsChanged()
{
	NotifyObservers();
}

void CProWeatherData::SetMeasurements(double temp, double humidity, double pressure, double windSpeed, double windDirection)
{
	m_events.clear();
	if (m_temperature != temp)
	{
		m_events.insert((size_t)WeatherInfoType::TEMPERATURE);
	}
	if (m_humidity != humidity)
	{
		m_events.insert((size_t)WeatherInfoType::HUMIDITY);
	}
	if (m_pressure != pressure)
	{
		m_events.insert((size_t)WeatherInfoType::PRESSURE);
	}
	if (m_windSpeed != windSpeed)
	{
		m_events.insert((size_t)WeatherInfoType::WIND_SPEED);
	}
	if (m_windDirection != windDirection)
	{
		m_events.insert((size_t)WeatherInfoType::WIND_DIRECTION);
	}

	m_humidity = humidity;
	m_temperature = temp;
	m_pressure = pressure;
	m_windSpeed = windSpeed;
	m_windDirection = windDirection;

	MeasurementsChanged();
}

const CProWeatherData * CProWeatherData::GetConcreteObservable() const
{
	return this;
}

const std::set<size_t> & CProWeatherData::GetEventIds() const
{
	return m_events;
}
