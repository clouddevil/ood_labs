// WeatherStationPro.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "WeatherData.h"

int main()
{
	CWeatherData wd;

	CStatsDisplay statsDisplay;
	wd.RegisterObserver(statsDisplay);

	wd.SetWind(10, 0);

	wd.SetWind(15, 180);
	wd.SetWind(5, 45);

	
	return 0;
}

