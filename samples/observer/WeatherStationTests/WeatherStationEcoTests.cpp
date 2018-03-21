#include "stdafx.h"
#include "..\WeatherStationEco\WeatherData.h"

using namespace eco;

namespace
{

template <typename T>
struct FunctionalObserver : public IObserver<T>
{
	using UpdateFunction = std::function<void(T const& data)>;

	int eventId = 0;
	UpdateFunction op = [](auto&&) {};

	FunctionalObserver(FunctionalObserver const& v)
		: op(v.op)
		, priority(v.priority)
	{

	}

	FunctionalObserver() = default;
	FunctionalObserver(UpdateFunction const& opn, int id = 0)
		: op(opn)
		, eventId(id)
	{
	}

	void Update(T const& data) override
	{
		op(data);
	}
};

}

BOOST_AUTO_TEST_SUITE(WeatherStationEcoTests)

BOOST_AUTO_TEST_CASE(ObserverNotification)
{
	

	using Observer = FunctionalObserver<SWeatherInfo>;
	
	std::vector<int> eventOrder;
	auto makeObserver = [&](int eventId) -> Observer {
		return { [&eventOrder, id = eventId](auto&&) {
			eventOrder.push_back(id);
		}, eventId };
	};

	Observer observer0 = makeObserver(1);
	Observer observer1 = makeObserver(1);
	Observer observer2 = makeObserver(0);
	Observer observer3 = makeObserver(2);	

	const int UnusedEventID = 100;	

	CWeatherData wd;
	wd.RegisterObserver(observer0, observer0.eventId);
	wd.RegisterObserver(observer1, observer1.eventId);
	wd.RegisterObserver(observer2, observer2.eventId);
	wd.RegisterObserver(observer3, observer3.eventId);	
	wd.RegisterObserver(observer3, observer3.eventId);
	wd.RegisterObserver(observer3, observer3.eventId + 100);

	wd.NotifyObservers(1);
	std::vector<int> expectedOrder{1, 1};
	BOOST_CHECK_EQUAL(eventOrder, expectedOrder);

	eventOrder.clear();
	expectedOrder = { 2 };
	wd.NotifyObservers(2);
	BOOST_CHECK_EQUAL(eventOrder, expectedOrder);

	eventOrder.clear();
	expectedOrder = { };
	wd.NotifyObservers(3);
	BOOST_CHECK_EQUAL(eventOrder, expectedOrder);

	eventOrder.clear();
	expectedOrder = {};
	wd.NotifyObservers(UnusedEventID);
	BOOST_CHECK_EQUAL(eventOrder, expectedOrder);

	wd.RemoveObserver(observer2, observer2.eventId);

	eventOrder.clear();
	expectedOrder = {};
	wd.NotifyObservers(observer2.eventId);
	BOOST_CHECK_EQUAL(eventOrder, expectedOrder);
}

BOOST_AUTO_TEST_SUITE_END()


