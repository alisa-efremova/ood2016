#pragma once
#include "IObserver.h"
#include "WeatherData.h"

class CDisplay : public IObserver<CWeatherData>
{
private:
	void Update(CWeatherData const& subject) override;
};

