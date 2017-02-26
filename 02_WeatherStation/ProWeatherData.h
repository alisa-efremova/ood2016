#pragma once
#include "Observable.h"
#include "WeatherStationLocation.h"

class CProWeatherData : public CObservable<CProWeatherData>
{
public:
	double GetTemperature()const;
	double GetHumidity()const;
	double GetPressure()const;
	double GetWindSpeed()const;
	double GetWindDirection()const;
	WeatherStationLocation GetLocation()const;

	void MeasurementsChanged();
	void SetMeasurements(double temp, double humidity, double pressure, double windSpeed, double windDirection);

protected:
	const CProWeatherData * GetConcreteObservable()const override;
	const std::set<size_t> & GetEventIds()const override;

private:
	double m_temperature = 0.0;
	double m_humidity = 0.0;
	double m_pressure = 760.0;
	double m_windSpeed = 0.0;
	double m_windDirection = 0;
	WeatherStationLocation m_location = WeatherStationLocation::OUT;
	std::set<size_t> m_events; // set of WeatherInfoType
};


