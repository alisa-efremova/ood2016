#pragma once
#include "IObserver.h"
#include "SWeatherInfo.h"

class CDisplay : public IObserver<SWeatherInfo>
{
private:
	void Update(SWeatherInfo const& data) override;
};

