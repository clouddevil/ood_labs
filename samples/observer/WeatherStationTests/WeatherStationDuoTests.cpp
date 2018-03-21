#include "stdafx.h"
#include "..\WeatherStationDuo\WeatherData.h"

namespace std
{

std::ostream& operator<<(std::ostream& stream, std::vector<IObservable<SWeatherInfo> const*> const& vec)
{
	for (auto&& v : vec)
	{
		stream << &(v) << " ";
	}
	return stream;
}

}

namespace
{

template <typename T>
struct FunctionalObserver : public IObserver<T>
{
	using UpdateFunction = std::function<void(IObservable<T> const& obj, T const& data)>;

	UpdateFunction op = [](auto const&, auto&&) {};

	FunctionalObserver(FunctionalObserver const& v)
		: op(v.op)	
	{
	}

	FunctionalObserver() = default;
	FunctionalObserver(UpdateFunction const& opn, int prty = 0)
		: op(opn)
		, priority(prty)
	{
	}

	void Update(IObservable<T> const& obj, T const& data) override
	{
		op(obj, data);
	}
};

}

BOOST_AUTO_TEST_SUITE(ObserverDuoTestSuite)

BOOST_AUTO_TEST_CASE(RemoveObserverInNotification)
{
	using Observer = FunctionalObserver<SWeatherInfo>;
	using ObservableVector = std::vector<IObservable<SWeatherInfo> const*>;

	CWeatherData wd1;
	CWeatherData wd2;

	Observer observer;
	wd1.RegisterObserver(observer);
	wd2.RegisterObserver(observer);

	ObservableVector observables;
	observer.op = [&](auto const& wd, auto&) {
		observables.push_back(&wd);
	};
	
	wd1.NotifyObservers();
	wd1.NotifyObservers();
	wd2.NotifyObservers();
	wd1.NotifyObservers();
	wd2.NotifyObservers();

	ObservableVector expectedObservables = {&wd1, &wd1, &wd2, &wd1, &wd2};
	BOOST_CHECK_EQUAL(observables.size(), 5);
	BOOST_CHECK_EQUAL(observables, expectedObservables);
}

BOOST_AUTO_TEST_SUITE_END()


