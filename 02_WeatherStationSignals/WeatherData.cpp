#include "stdafx.h"
#include "WeatherData.h"

void CWeatherData::SetMeasurements(double temp, double humidity, double pressure)
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
}

signals::connection CWeatherData::DoOnTemperatureChange(const WeatherSignal::slot_type & slot)
{
	return m_temperatureChangeSignal.connect(slot);
}

signals::connection CWeatherData::DoOnHumidityChange(const WeatherSignal::slot_type & slot)
{
	return m_humidityChangeSignal.connect(slot);
}

signals::connection CWeatherData::DoOnPressureChange(const WeatherSignal::slot_type & slot)
{
	return m_pressureChangeSignal.connect(slot);
}

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