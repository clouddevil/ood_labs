// WeatherStationDuo.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "WeatherData.h"

int main()
{
	CWeatherData wd1;
	CWeatherData wd2;

	CDisplay display;
	wd1.RegisterObserver(display);
	wd2.RegisterObserver(display);

	wd1.SetMeasurements(1, 0.7, 760);
	wd2.SetMeasurements(2, 4.7, -760);

	wd2.RemoveObserver(display);

	wd2.SetMeasurements(3, 2.7, 760);	// no dispatch

	return 0;
}

