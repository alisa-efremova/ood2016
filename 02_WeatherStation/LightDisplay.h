#pragma once
#include "IObserver.h"
class CProWeatherData;

class CLightDisplay : public IObserver<CProWeatherData>
{
public:
	CLightDisplay();
	
private:
	void Update(CProWeatherData const& subject) override;
};

