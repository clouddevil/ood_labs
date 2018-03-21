#include "stdafx.h"
#include "..\WeatherStation\WeatherData.h"

namespace
{

template <typename T>
struct FunctionalObserver : public IObserver<T>
{
	using UpdateFunction = std::function<void(T const& data)>;
	
	int priority = 0;
	UpdateFunction op = [](auto&&) {};

	FunctionalObserver(FunctionalObserver const& v)
		: op(v.op)
		, priority(v.priority)
	{

	}
	
	FunctionalObserver() = default;
	FunctionalObserver(UpdateFunction const& opn, int prty = 0)
		: op(opn)
		, priority(prty)
	{
	}

	void Update(T const& data) override
	{
		op(data);	
	}	
};

}

BOOST_AUTO_TEST_SUITE(ObserverTestSuite)

BOOST_AUTO_TEST_CASE(RemoveObserverInNotification)
{
	using Observer = FunctionalObserver<SWeatherInfo>;

	CWeatherData wd;
	Observer observer;

	observer.op = [&](auto&&) {
		wd.RemoveObserver(observer);
	};

 	wd.RegisterObserver(observer);
 	wd.NotifyObservers();
}

BOOST_AUTO_TEST_CASE(ObserverNotificationPriority)
{
	using Observer = FunctionalObserver<SWeatherInfo>;

	std::vector<int> order;
	auto makeObserver = [&order](int p) -> Observer {
		return{ [&order, priority = p](auto&&) {
			order.push_back(priority);
		}, p };
	};

	Observer observer0 = makeObserver(-100);
	Observer observer1 = makeObserver(0);
	Observer observer2 = makeObserver(42);
	Observer observer3 = makeObserver(43);
	Observer observer4 = makeObserver(666);
	Observer observer5 = makeObserver(43);

	CWeatherData wd;
	wd.RegisterObserver(observer0, observer0.priority);
	wd.RegisterObserver(observer1, observer1.priority);
	wd.RegisterObserver(observer2, observer2.priority);
	wd.RegisterObserver(observer3, observer3.priority);
	wd.RegisterObserver(observer4, observer4.priority);

	wd.RegisterObserver(observer5, observer5.priority);
	wd.RegisterObserver(observer5, 146); // register same object with other priority, replace it
	wd.RegisterObserver(observer5, observer5.priority); // register same object with same priority	
	wd.NotifyObservers();

	std::vector<int> expectedOrder(order);
	std::sort(expectedOrder.begin(), expectedOrder.end(), std::greater<int>());

	BOOST_CHECK_EQUAL(order.size(), 6);
	BOOST_CHECK_EQUAL(order, expectedOrder);
}

BOOST_AUTO_TEST_SUITE_END()


