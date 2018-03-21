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
	double windSpeed = 0;
	double windDirection = 0;
};

struct SStatInfo
{
	double m_minValue = std::numeric_limits<double>::infinity();
	double m_maxValue = -std::numeric_limits<double>::infinity();
	double m_accValue = 0;
	unsigned m_countAcc = 0;
};

class CDisplay: public IObserver<SWeatherInfo>
{
private:
	void Update(SWeatherInfo const& data) override
	{
		std::cout << "Current Temp " << data.temperature << std::endl;
		std::cout << "Current Hum " << data.humidity << std::endl;
		std::cout << "Current Pressure " << data.pressure << std::endl;
		std::cout << "Current Wind Speed " << data.windSpeed << std::endl;
		std::cout << "Current Wind Direction " << data.windDirection << std::endl;
		std::cout << "----------------" << std::endl;
	}
};

class Statistic
{
public:		
	void UpdateStatWith(double value)
	{
		if (m_stat.m_minValue > value)
		{
			m_stat.m_minValue = value;
		}
		if (m_stat.m_maxValue < value)
		{
			m_stat.m_maxValue = value;
		}
		m_stat.m_accValue += value;
		++m_stat.m_countAcc;		
	}

	SStatInfo const& GetStatInfo() const
	{
		return m_stat;
	}
	
private:
	SStatInfo m_stat;
};

class WindDirectionStatistic
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

class CStatsDisplay : public IObserver<SWeatherInfo>
{
private:
	static void DisplayStatInfo(SStatInfo const& info, std::string const& infoName)
	{
		std::cout << "Max " << infoName.c_str() << " " << info.m_maxValue << std::endl;
		std::cout << "Min " << infoName.c_str() << " " << info.m_minValue << std::endl;
		std::cout << "Average " << infoName.c_str() << " " << (info.m_accValue / info.m_countAcc) << std::endl;
		std::cout << "----------------" << std::endl;
	}

	void Update(SWeatherInfo const& data) override
	{
		std::cout << "*******************" << std::endl;

		m_temperatureStat.UpdateStatWith(data.temperature);
		DisplayStatInfo(m_temperatureStat.GetStatInfo(), "Temp");

		m_pressureStat.UpdateStatWith(data.pressure);
		DisplayStatInfo(m_pressureStat.GetStatInfo(), "Pressure");

		m_humidityStat.UpdateStatWith(data.humidity);
		DisplayStatInfo(m_pressureStat.GetStatInfo(), "Hum");

		m_windSpeedStat.UpdateStatWith(data.windSpeed);
		DisplayStatInfo(m_windSpeedStat.GetStatInfo(), "Wind");
		
		m_windDirectionStat.UpdateStatWith(data.windDirection);
		m_windDirectionStat.Display();

		std::cout << "*******************" << std::endl;
	}

	Statistic m_temperatureStat;
	Statistic m_pressureStat;
	Statistic m_humidityStat;
	Statistic m_windSpeedStat;
	WindDirectionStatistic m_windDirectionStat;
};

class CWeatherData : public CObservable<SWeatherInfo>
{
public:	
	double GetTemperature()const
	{
		return m_info.temperature;
	}
	
	double GetHumidity()const
	{
		return m_info.humidity;
	}

	double GetPressure()const
	{
		return m_info.pressure;
	}

	double GetWindSpeed()const
	{
		return m_info.windSpeed;
	}

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

	void SetWind(double speed, double direction)
	{
		m_info.windSpeed = speed;
		m_info.windDirection = direction;

		MeasurementsChanged();
	}

protected:
	SWeatherInfo GetChangedData()const override
	{		
		return m_info;
	}
private:
	SWeatherInfo m_info;
};
