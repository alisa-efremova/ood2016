#include "stdafx.h"
#include "WeatherData.h"
#include "WeatherInfoType.h"

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

void CWeatherData::MeasurementsChanged()
{
	NotifyObservers();
}

void CWeatherData::SetMeasurements(double temp, double humidity, double pressure)
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

	m_humidity = humidity;
	m_temperature = temp;
	m_pressure = pressure;

	MeasurementsChanged();
}

const CWeatherData * CWeatherData::GetConcreteObservable()const
{
	return this;
}

const std::set<size_t> & CWeatherData::GetEventIds()const
{
	return m_events;
}
