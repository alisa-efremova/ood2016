#include "IObserver.h"
#include "WeatherData.h"
#include "SWeatherInfo.h"
#include <memory>

class CMockUnsubscribingObserver : public IObserver<SWeatherInfo>
{
public:
	CMockUnsubscribingObserver(CWeatherData & weatherData)
	: m_weatherData(weatherData)
	{
		m_weatherData.RegisterObserver(*this);
	}

private:
	void Update(SWeatherInfo const& data) override
	{
		m_weatherData.RemoveObserver(*this);
	}

	CWeatherData & m_weatherData;
};