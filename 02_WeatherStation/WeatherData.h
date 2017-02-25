#pragma once
#include "Observable.h"
#include "SWeatherInfo.h"
#include "WeatherStationLocation.h"

class CWeatherData : public CObservable<CWeatherData>
{
public:
	// ����������� � �������� �������
	double GetTemperature()const;

	// ������������� ��������� (0...100)
	double GetHumidity()const;

	// ����������� �������� (� ��.��.��)
	double GetPressure()const;

	void MeasurementsChanged();
	void SetMeasurements(double temp, double humidity, double pressure);

protected:
	const CWeatherData * GetConcreteObservable()const override;
	const std::set<size_t> & GetEventIds()const override;
	
private:
	double m_temperature = 0.0;
	double m_humidity = 0.0;
	double m_pressure = 760.0;
	std::set<size_t> m_events; // set of WeatherInfoType
};

