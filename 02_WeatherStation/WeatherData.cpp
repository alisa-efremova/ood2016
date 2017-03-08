#include "stdafx.h"
#include "WeatherData.h"

double CWeatherData::GetTemperature() const
{
	return m_temperature;
}

double CWeatherData::GetHumidity() const
{
	return m_humidity;
}

double CWeatherData::GetPressure() const
{
	return m_pressure;
}

WeatherStationLocation CWeatherData::GetLocation() const
{
	return m_location;
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
		m_events.insert(WeatherInfoType::TEMPERATURE);
	}
	if (m_humidity != humidity)
	{
		m_events.insert(WeatherInfoType::HUMIDITY);
	}
	if (m_pressure != pressure)
	{
		m_events.insert(WeatherInfoType::PRESSURE);
	}

	m_humidity = humidity;
	m_temperature = temp;
	m_pressure = pressure;

	MeasurementsChanged();
}

const CWeatherData * CWeatherData::GetConcreteObservable() const
{
	return this;
}

std::set<boost::optional<WeatherInfoType>> & CWeatherData::GetEventTypes()
{
	return m_events;
}
