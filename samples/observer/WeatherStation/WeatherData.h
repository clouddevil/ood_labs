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
};

struct SStatInfo
{
	double minValue = std::numeric_limits<double>::infinity();
	double maxValue = -std::numeric_limits<double>::infinity();
	double accValue = 0;
	unsigned countAcc = 0;
};

class CDisplay: public IObserver<SWeatherInfo>
{
private:
	void Update(SWeatherInfo const& data) override
	{
		std::cout << "Current Temp " << data.temperature << std::endl;
		std::cout << "Current Hum " << data.humidity << std::endl;
		std::cout << "Current Pressure " << data.pressure << std::endl;
		std::cout << "----------------" << std::endl;
	}
};

class Statistic
{
public:		
	void UpdateStatWith(double value)
	{
		if (m_stat.minValue > value)
		{
			m_stat.minValue = value;
		}
		if (m_stat.maxValue < value)
		{
			m_stat.maxValue = value;
		}
		m_stat.accValue += value;
		++m_stat.countAcc;		
	}

	SStatInfo const& GetStatInfo() const
	{
		return m_stat;
	}
	
private:
	SStatInfo m_stat;
};

class CStatsDisplay : public IObserver<SWeatherInfo>
{
private:
	static void DisplayStatInfo(SStatInfo const& info, std::string const& infoName)
	{
		std::cout << "Max " << infoName.c_str() << " " << info.maxValue << std::endl;
		std::cout << "Min " << infoName.c_str() << " " << info.minValue << std::endl;
		std::cout << "Average " << infoName.c_str() << " " << (info.accValue / info.countAcc) << std::endl;
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

		std::cout << "*******************" << std::endl;
	}

	Statistic m_temperatureStat;
	Statistic m_pressureStat;
	Statistic m_humidityStat;
};

class CWeatherData : public CObservable<SWeatherInfo>
{
public:
	// Температура в градусах Цельсия
	double GetTemperature()const
	{
		return m_temperature;
	}
	// Относительная влажность (0...100)
	double GetHumidity()const
	{
		return m_humidity;
	}
	// Атмосферное давление (в мм.рт.ст)
	double GetPressure()const
	{
		return m_pressure;
	}

	void MeasurementsChanged()
	{
		NotifyObservers();
	}

	void SetMeasurements(double temp, double humidity, double pressure)
	{
		m_humidity = humidity;
		m_temperature = temp;
		m_pressure = pressure;

		MeasurementsChanged();
	}
protected:
	SWeatherInfo GetChangedData()const override
	{
		SWeatherInfo info;
		info.temperature = GetTemperature();
		info.humidity = GetHumidity();
		info.pressure = GetPressure();
		return info;
	}
private:
	double m_temperature = 0.0;
	double m_humidity = 0.0;	
	double m_pressure = 760.0;	
};
