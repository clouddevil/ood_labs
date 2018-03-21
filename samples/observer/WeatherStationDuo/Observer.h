#pragma once

#include <set>
#include <functional>

template <typename T>
class IObservable;


template <typename T>
class IObserver
{
public:
	virtual void Update(IObservable<T> const& obj, T const& data) = 0;
	virtual ~IObserver() = default;
};

template <typename T>
class IObservable
{
public:
	virtual ~IObservable() = default;
	virtual void RegisterObserver(IObserver<T> & observer, int priority) = 0;
	virtual void NotifyObservers() = 0;
	virtual void RemoveObserver(IObserver<T> & observer) = 0;
};


template <class T>
struct ObserverWrapper
{
public:	
	ObserverWrapper(IObserver<T>* obj, int prty = 0)
		: priority(prty)
		, observer(obj)
	{
	}

	int priority = 0;
	IObserver<T>* observer = nullptr;	
};

template<typename T>
bool operator<(ObserverWrapper<T> const& a, ObserverWrapper<T> const& b)
{
	auto rank = [](auto const& v) {
		return std::make_tuple(v.priority, v.observer);
	};
	// reverse order
	return rank(a) > rank(b);
}

// Реализация интерфейса IObservable
template <class T>
class CObservable : public IObservable<T>
{
public:
	using ObserverType = IObserver<T>;

	void RegisterObserver(ObserverType & observer, int priority = 0) override
	{		
		RemoveObserver(observer);
		m_observers.emplace(&observer, priority);
	}

	void NotifyObservers() override
	{
		T data = GetChangedData();

		auto safeObservers(m_observers);
		for (auto & v : safeObservers)
		{
			v.observer->Update(*this, data);
		}
	}

	void RemoveObserver(ObserverType & observer) override
	{
		auto it = std::find_if(m_observers.begin(), m_observers.end(), [&](auto const& v) {
			return (v.observer == &observer);
		});
		if (it != m_observers.end())
		{
			m_observers.erase(it);
		}
	}

protected:
	// Классы-наследники должны перегрузить данный метод, 
	// в котором возвращать информацию об изменениях в объекте
	virtual T GetChangedData()const = 0;

private:
	std::set<ObserverWrapper<T>> m_observers;
};
