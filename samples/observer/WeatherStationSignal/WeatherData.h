#pragma once
#pragma warning(disable: 4996 4512 4702 4100 4503)

#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

#include "SignallingValue.h"

using namespace std;

struct SWeatherInfo
{
	double temperature = 0;
	double humidity = 0;
	double pressure = 0;	

	auto rank() const 
	{
		return std::make_tuple(temperature, humidity, pressure);
	}

	bool operator!=(SWeatherInfo const& v) const
	{
		return rank() != v.rank();
	}
};

struct SWindInfo
{
	double windSpeed = 0;
	double windDirection = 0;

	auto rank() const
	{
		return std::make_tuple(windSpeed, windDirection);
	}

	bool operator!=(SWindInfo const& v) const
	{
		return rank() != v.rank();
	}
};


struct SStatInfo
{
	double minValue = std::numeric_limits<double>::infinity();
	double maxValue = -std::numeric_limits<double>::infinity();
	double accValue = 0;
	unsigned countAcc = 0;

	void UpdateStatWith(double value)
	{
		if (minValue > value)
		{
			minValue = value;
		}
		if (maxValue < value)
		{
			maxValue = value;
		}
		accValue += value;
		++countAcc;
	}

	void Display(std::string const& infoName)
	{
		std::cout << "Max " << infoName.c_str() << " " << maxValue << std::endl;
		std::cout << "Min " << infoName.c_str() << " " << minValue << std::endl;
		std::cout << "Average " << infoName.c_str() << " " << (accValue / countAcc) << std::endl;
		std::cout << "----------------" << std::endl;
	}
};

struct SWindDisplay
{
	void Display(SWindInfo const& data)
	{		
		std::cout << "Current Wind Speed " << data.windSpeed << std::endl;
		std::cout << "Current Wind Direction " << data.windDirection << std::endl;
		std::cout << "----------------" << std::endl;
	}
};

struct SWeatherDisplay
{
	void Display(SWeatherInfo const& data)
	{
		std::cout << "Current Temp " << data.temperature << std::endl;
		std::cout << "Current Hum " << data.humidity << std::endl;
		std::cout << "Current Pressure " << data.pressure << std::endl;		
		std::cout << "----------------" << std::endl;
	}
};

struct SWindDirectionStatInfo
{
	void UpdateStatWith(double direction)
	{		
		auto radDirection = direction  * M_PI / 180.0;
		direction0 += std::max<>(0.0, std::cos(radDirection));
		direction90 += std::max<>(0.0, std::sin(radDirection));
		direction180 += std::max<>(0.0, std::cos(radDirection + M_PI));
		direction270 += std::max<>(0.0, std::sin(radDirection - M_PI));
	}

	void Display()
	{
		auto total = direction0 + direction90 + direction180 + direction270;
		if (total < std::numeric_limits<double>::epsilon())
		{
			std::cout << "No wind stat!" << std::endl;
		}
		else
		{			
			ios::fmtflags state(cout.flags());
			std::cout << std::fixed;

			std::cout << "Wind direction stat:" << std::endl;
			
			std::cout << "  0 : " << direction0 / total << std::endl;
			std::cout << " 90 : " << direction90 / total << std::endl;
			std::cout << "180 : " << direction180 / total << std::endl;
			std::cout << "270 : " << direction270 / total << std::endl;
			std::cout.flags(state);
		}		
	}

	double direction0 = 0.0f;
	double direction90 = 0.0f;
	double direction180 = 0.0f;
	double direction270 = 0.0f;
};

struct SStatsDisplay
{
	void UpdateWeather(SWeatherInfo const& data)
	{
		m_temperatureStat.UpdateStatWith(data.temperature);
		m_pressureStat.UpdateStatWith(data.pressure);
		m_humidityStat.UpdateStatWith(data.humidity);		
	}

	void UpdateWind(SWindInfo const& data)
	{
		m_windSpeedStat.UpdateStatWith(data.windSpeed);
		m_windDirectionStat.UpdateStatWith(data.windDirection);
	}

	void Display()
	{
		m_temperatureStat.Display("Temp");
		m_pressureStat.Display("Pressure");
		m_humidityStat.Display("Hum");
		m_windSpeedStat.Display("Wind");
		m_windDirectionStat.Display();
	}

	SStatInfo m_temperatureStat;
	SStatInfo m_pressureStat;
	SStatInfo m_humidityStat;
	SStatInfo m_windSpeedStat;
	SWindDirectionStatInfo m_windDirectionStat;
};

class CWeatherData
{
public:
	void SetMeasurements(double temp, double humidity, double pressure)
	{
		SWeatherInfo weatherInfo;
		weatherInfo.humidity = humidity;
		weatherInfo.temperature = temp;
		weatherInfo.pressure = pressure;

		m_weatherInfo = weatherInfo;
	}

	void SetWind(double speed, double direction)
	{
		SWindInfo windInfo;
		windInfo.windSpeed = speed;
		windInfo.windDirection = direction;

		m_windInfo = windInfo;
	}

	Connection DoOnWindChange(SignallingValue<SWindInfo>::Slot1 const& handler)
	{
		return m_windInfo.Connect1(handler, false);
	}

	Connection DoOnWeatherChange(SignallingValue<SWeatherInfo>::Slot1 const& handler)
	{
		return m_weatherInfo.Connect1(handler, false);
	}

private:
	SignallingValue<SWindInfo> m_windInfo;
	SignallingValue<SWeatherInfo> m_weatherInfo;
};
