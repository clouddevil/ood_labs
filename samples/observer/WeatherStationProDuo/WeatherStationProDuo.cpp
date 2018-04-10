// WeatherStationProDuo.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "WeatherData.h"

int main()
{
	CWeatherDataBasic wd1;
	CWeatherDataPro wd2;
	
	CStatsDisplayPro displayPro;
	CStatsDisplayBasic displayBasic;	

	wd1.RegisterObserver(displayBasic);
	wd2.RegisterObserver(displayPro);

	wd1.SetMeasurements(1, 0.7, 760);
	wd2.SetMeasurements(2, 4.7, -760);
	wd2.SetWind(10, 45);

	//wd2.RemoveObserver(display);

	wd2.SetMeasurements(3, 2.7, 760);	// no dispatch

	return 0;
}

