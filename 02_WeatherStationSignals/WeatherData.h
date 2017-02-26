#pragma once

#include <boost/noncopyable.hpp>
#include <boost/signals2.hpp>

namespace signals = boost::signals2;

template <class T>
class IWeatherData
{
public:
	virtual signals::connection DoOnChange(const typename signals::signal<void(const T *)>::slot_type & slot) = 0;
	virtual ~IWeatherData() = default;
};

class CWeatherData : public IWeatherData<CWeatherData>
{
public:
	void SetMeasurements(double temp, double humidity, double pressure)
	{
		m_humidity = humidity;
		m_temperature = temp;
		m_pressure = pressure;

		m_changeSignal(this);
	}

	virtual signals::connection DoOnChange(const signals::signal<void(const CWeatherData *)>::slot_type & slot) override
	{
		return m_changeSignal.connect(slot);
	}

	double GetTemperature()const
	{
		return m_temperature;
	}

	double GetHumidity()const
	{
		return m_humidity;
	}

	double GetPressure()const
	{
		return m_pressure;
	}

private:
	double m_temperature = 59.0;
	double m_humidity = 0.0;
	double m_pressure = 760.0;
	signals::signal<void(const CWeatherData *)>	m_changeSignal;
};

#if 1
class CProWeatherData : public IWeatherData<CProWeatherData>
{
public:
	void CProWeatherData::SetMeasurements(double temp, double humidity, double pressure, double windSpeed, double windDirection)
	{
		m_humidity = humidity;
		m_temperature = temp;
		m_pressure = pressure;
		m_windSpeed = windSpeed;
		m_windDirection = windDirection;

		m_changeSignal(this);
	}

	virtual signals::connection DoOnChange(const signals::signal<void(const CProWeatherData *)>::slot_type & slot) override
	{
		return m_changeSignal.connect(slot);
	}

	double CProWeatherData::GetTemperature()const
	{
		return m_temperature;
	}

	double CProWeatherData::GetHumidity()const
	{
		return m_humidity;
	}

	double CProWeatherData::GetPressure()const
	{
		return m_pressure;
	}

	double CProWeatherData::GetWindSpeed()const
	{
		return m_windSpeed;
	}

	double CProWeatherData::GetWindDirection()const
	{
		return m_windDirection;
	}

private:
	double m_temperature = 0.0;
	double m_humidity = 0.0;
	double m_pressure = 760.0;
	double m_windSpeed = 0.0;
	double m_windDirection = 0;
	signals::signal<void(const CProWeatherData *)> m_changeSignal;
};
#endif
