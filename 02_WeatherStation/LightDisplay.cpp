#include "stdafx.h"
#include "LightDisplay.h"
#include "ProWeatherData.h"

using namespace std;

CLightDisplay::CLightDisplay()
{
}

void CLightDisplay::Update(CProWeatherData const& subject)
{
	cout << "----------------------------------------------------------------" << endl;
	cout << "* CURRENT light*" << endl;
	cout << "Temperature:\t" << subject.GetTemperature() << endl;
	cout << "Pressure:\t" << subject.GetPressure() << endl;
	cout << "----------------------------------------------------------------" << endl;
}