#pragma once
#include "Observable.h"
#include "WeatherStationLocation.h"
#include "WeatherInfoType.h"

class CWeatherData : public CObservable<CWeatherData, WeatherInfoType>
{
public:
	// Температура в градусах Цельсия
	double GetTemperature()const;

	// Относительная влажность (0...100)
	double GetHumidity()const;

	// Атмосферное давление (в мм.рт.ст)
	double GetPressure()const;

	WeatherStationLocation GetLocation()const;

	void MeasurementsChanged();
	void SetMeasurements(double temp, double humidity, double pressure);

protected:
	const CWeatherData * GetConcreteObservable()const override;
	std::set<boost::optional<WeatherInfoType>> & GetEventTypes() override;
	
private:
	double m_temperature = 0.0;
	double m_humidity = 0.0;
	double m_pressure = 760.0;
	WeatherStationLocation m_location = WeatherStationLocation::IN;
	std::set<boost::optional<WeatherInfoType>> m_events; // set of WeatherInfoType
};

