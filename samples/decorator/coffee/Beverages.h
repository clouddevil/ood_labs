#pragma once

#include "IBeverage.h"

// Базовая реализация напитка, предоставляющая его описание
class CBeverage : public IBeverage
{
public:
	CBeverage(const std::string & description, double cost = 0.0f)
		:m_description(description)		
		,m_cost(cost)
	{}

	double GetCost() const override
	{
		return m_cost;
	}

	std::string GetDescription()const override final
	{
		return m_description + " x" + std::to_string(m_quantity);
	}

	void InitCostForQuantity(unsigned beverageQantity, std::vector<double> costs)
	{
		auto maxQuantity = static_cast<unsigned>(std::size(costs));
		auto quantity = clamp(beverageQantity, 1u, maxQuantity);

		m_quantity = quantity;
		m_cost = costs[quantity - 1];
	}

private:
	double m_cost = 0.0;
	unsigned m_quantity = 1;
	std::string m_description;
};

// Кофе
class CCoffee : public CBeverage
{
public:
	CCoffee(const std::string& description = "Coffee")
		:CBeverage(description) 
	{}
	
};

// Капуччино
class CCapuccino : public CCoffee
{
public:
	CCapuccino(unsigned quantity)
		:CCoffee("Capuccino") 
	{
		InitCostForQuantity(quantity, { 80.0, 120.0});
	}
};

// Латте
class CLatte : public CCoffee
{
public:
	CLatte(unsigned quantity)
		:CCoffee("Latte") 
	{
		InitCostForQuantity(quantity, { 90.0, 130.0 });
	}	
};

// Чай
class CTea : public CBeverage
{
public:
	CTea(const std::string& kindOfTea)
		:CBeverage(kindOfTea + " Tea", 30)
	{}	
};

// Молочный коктейль
class CMilkshake : public CBeverage
{
public:
	CMilkshake(unsigned shakeQuantity)
		:CBeverage("Milkshake")
	{
		InitCostForQuantity(shakeQuantity, { 50.0, 60.0, 80.0 });
	}
};
