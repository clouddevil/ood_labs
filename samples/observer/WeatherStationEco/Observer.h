#pragma once

#include <set>
#include <functional>


namespace eco
{

template <typename T>
class IObserver
{
public:
	virtual void Update(T const& data) = 0;
	virtual ~IObserver() = default;
};

template <typename T>
class IObservable
{
public:
	virtual ~IObservable() = default;
	virtual void RegisterObserver(IObserver<T> & observer, int eventId, int priority) = 0;
	virtual void NotifyObservers(int eventId) = 0;
	virtual void RemoveObserver(IObserver<T> & observer, int eventId) = 0;
};


template <class T>
struct ObserverWrapper
{
public:	
	ObserverWrapper(IObserver<T>* obj, int entId = 0, int prty = 0)
		: priority(prty)
		, observer(obj)
		, eventId(entId)
	{
	}

	int priority = 0;
	int eventId = 0;
	IObserver<T>* observer = nullptr;
};

template<typename T>
bool operator<(ObserverWrapper<T> const& a, ObserverWrapper<T> const& b)
{
	auto rank = [](ObserverWrapper<T> const& v) {
		return std::make_tuple(v.priority, v.observer, v.eventId);
	};
	// reverse order
	return rank(a) > rank(b);
}


template <class T>
class CObservable : public IObservable<T>
{
public:
	using ObserverType = IObserver<T>;

	void RegisterObserver(ObserverType & observer, int eventId, int priority = 0) override
	{		
		RemoveObserver(observer, eventId);
		m_observers.emplace(&observer, eventId, priority);		
	}

	void NotifyObservers(int eventId) override
	{
		T data = GetChangedData();

		auto safeObservers(m_observers);
		for (auto & v : safeObservers)
		{
			if (v.eventId == eventId)
			{
				v.observer->Update(data);
			}			
		}
	}

	void RemoveObserver(ObserverType& observer, int eventId) override
	{
		auto it = std::find_if(m_observers.begin(), m_observers.end(), [&](auto const& v) {
			return ((v.observer == &observer) && (v.eventId == eventId));
		});
		if (it != m_observers.end())
		{
			m_observers.erase(it);
		}
	}

protected:	
	virtual T GetChangedData()const = 0;

private:
	std::set<ObserverWrapper<T>> m_observers;
};


}
