#include "IObserver.h"
#include "WeatherData.h"
#include "SWeatherInfo.h"
#include <memory>

class CMockDisplay : public IObserver<SWeatherInfo>
{
public:
	CMockDisplay(CWeatherData & weatherData)
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