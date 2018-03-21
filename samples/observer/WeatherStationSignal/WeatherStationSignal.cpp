// WeatherStationSignal.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "WeatherData.h"
#include <functional>


int main()
{
	CWeatherData wd;

	//SWindDisplay windDisplay;
	//SWeatherDisplay weatherDisplay;
	SStatsDisplay statsDisplay;

	//ScopedConnection windChangeConnection = wd.DoOnWindChange(std::bind(&SWindDisplay::Display, windDisplay, std::placeholders::_1));
	//ScopedConnection weatherChangeConnection = wd.DoOnWeatherChange(std::bind(&SWeatherDisplay::Display, weatherDisplay, std::placeholders::_1));
	

	ScopedConnection windStatsChangeConnection = wd.DoOnWindChange(std::bind(&SStatsDisplay::UpdateWind, &statsDisplay, std::placeholders::_1));
	ScopedConnection weatherStatsChangeConnection = wd.DoOnWeatherChange(std::bind(&SStatsDisplay::UpdateWeather, &statsDisplay, std::placeholders::_1));
	
	wd.SetMeasurements(10, 20, 780);
	wd.SetMeasurements(10, 20, 780);


	statsDisplay.Display();


    return 0;
}

