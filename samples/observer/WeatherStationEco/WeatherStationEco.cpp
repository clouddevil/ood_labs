// WeatherStationEco.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "WeatherData.h"

int main()
{	
	using namespace eco;

	CWeatherData wd;

	CDisplayWind wind;
	CDisplayMeasurements measurements;

	wd.RegisterObserver(wind, WIND_CHANGE_EVENT_ID);
	wd.RegisterObserver(measurements, MEASUREMENTS_CHANGE_EVENT_ID);

	wd.SetMeasurements(1, 0.7, 760);
	wd.SetMeasurements(2, 4.7, -760);

	wd.RemoveObserver(measurements, MEASUREMENTS_CHANGE_EVENT_ID);

	wd.SetMeasurements(3, 2.7, 760);

	wd.SetWind(1, 40);

	return 0;
}

