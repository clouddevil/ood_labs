#pragma once

#include <string>
#include <algorithm>
#include <memory>
#include <vector>


// Интерфейс "напиток"
class IBeverage
{
public:
	virtual std::string GetDescription() const = 0;
	virtual double GetCost()const = 0;
	virtual ~IBeverage() = default;
};

typedef std::unique_ptr<IBeverage> IBeveragePtr;


template <class T> 
constexpr const T& clamp(const T& v, const T& lo, const T& hi)
{
	return std::max<T>(lo, std::min<T>(v, hi));
}
