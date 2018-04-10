#pragma once
#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
#include "Observer.h"

using namespace std;

struct SWeatherInfo
{
	double temperature = 0;
	double humidity = 0;
	double pressure = 0;

	virtual void Display() 
	{
		std::cout << "Current Temp " << temperature << std::endl;
		std::cout << "Current Hum " << humidity << std::endl;
		std::cout << "Current Pressure " << pressure << std::endl;
	}
};

struct SWeatherInfoPro
	: SWeatherInfo
{
	double windSpeed = 0;
	double windDirection = 0;

	void Display() final
	{
		SWeatherInfo::Display();

		std::cout << "Current Wind Speed " << windSpeed << std::endl;
		std::cout << "Current Wind Direction " << windDirection << std::endl;
	}
};

struct SStatInfo
{
	double minValue = std::numeric_limits<double>::infinity();
	double maxValue = -std::numeric_limits<double>::infinity();
	double accValue = 0;
	unsigned countAcc = 0;

	void Display(std::string const& infoName)
	{
		std::cout << "Max " << infoName.c_str() << " " << maxValue << std::endl;
		std::cout << "Min " << infoName.c_str() << " " << minValue << std::endl;
		std::cout << "Average " << infoName.c_str() << " " << (accValue / countAcc) << std::endl;		
	}

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
};


class SWindDirectionStatInfo
{
public:
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

private:
	double direction0 = 0.0f;
	double direction90 = 0.0f;
	double direction180 = 0.0f;
	double direction270 = 0.0f;
};

template<typename T>
class CStatsDisplay : public IObserver<T>
{
protected:
	void Update(T const& data) override
	{	
		m_temperatureStat.UpdateStatWith(data.temperature);
		m_temperatureStat.Display("Temp");		

		m_pressureStat.UpdateStatWith(data.pressure);
		m_pressureStat.Display("Pressure");

		m_humidityStat.UpdateStatWith(data.humidity);
		m_humidityStat.Display("Hum");

		std::cout << std::endl;
	}

	SStatInfo m_temperatureStat;
	SStatInfo m_pressureStat;
	SStatInfo m_humidityStat;
};

using CStatsDisplayBasic = CStatsDisplay<SWeatherInfo>;

class CStatsDisplayPro 
	: public CStatsDisplay<SWeatherInfoPro>
{
private:
	void Update(SWeatherInfoPro const& data) override
	{
		CStatsDisplay<SWeatherInfoPro>::Update(data);

		m_windSpeedStat.UpdateStatWith(data.windSpeed);
		m_windSpeedStat.Display("Wind");
		
		m_windDirectionStat.UpdateStatWith(data.windDirection);
		m_windDirectionStat.Display();
	}

	SStatInfo m_windSpeedStat;
	SWindDirectionStatInfo m_windDirectionStat;
};

template <typename TWeatherInfo>
class CWeatherData : public CObservable<TWeatherInfo>
{
public:
	void MeasurementsChanged()
	{
		NotifyObservers();
	}

	void SetMeasurements(double temp, double humidity, double pressure)
	{
		m_info.humidity = humidity;
		m_info.temperature = temp;
		m_info.pressure = pressure;

		MeasurementsChanged();
	}

protected:
	TWeatherInfo GetChangedData()const override
	{		
		return m_info;
	}	
private:
	TWeatherInfo m_info;
};

using CWeatherDataBasic = CWeatherData<SWeatherInfo>;

class CWeatherDataPro
	: public CWeatherData<SWeatherInfoPro>
{
public:
	void SetWind(double speed, double direction)
	{
		auto& info = GetChangedData();
		info.windSpeed = speed;
		info.windDirection = direction;

		MeasurementsChanged();
	}
};
