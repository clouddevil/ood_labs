#pragma once

using FlyBehavior = std::function<void(int)>;
using QuackBehavior = std::function<void()>;
using DanceBehavior = std::function<void()>;

struct BehaviorFactory
{	
	FlyBehavior FlyWithWings()
	{
		return [](int flightNumber)
		{
			cout << "I'm flying " << flightNumber << " with wings!!" << endl;
		};
	}

	DanceBehavior DanceWaltz()
	{
		return []()
		{
			cout << "Dancing waltz" << endl;
		};
	}

	DanceBehavior DanceMinuet()
	{
		return []()
		{
			cout << "Dancing minuet" << endl;
		};
	}

	QuackBehavior QuackQuack()
	{
		return []()
		{
			cout << "Quack Quack!!!" << endl;
		};
	}

	QuackBehavior QuackSqueak()
	{
		return []()
		{
			cout << "Squeek!!!" << endl;
		};
	}
};

class Duck
{
public:
	void SetFlyBehavior(FlyBehavior&& flyBehavior)
	{
		m_flyBehavior = move(flyBehavior);
	}

	void SetQuackBehavior(QuackBehavior&& quackBehavior)
	{
		m_quackBehavior = move(quackBehavior);
	}

	void SetDanceBehavior(DanceBehavior&& danceBehavior)
	{
		m_danceBehavior = move(danceBehavior);
	}

	void Quack() const
	{
		if (m_quackBehavior)
		{
			m_quackBehavior();
		}
	}

	void Fly()
	{
		if (m_flyBehavior)
		{
			++m_flightNumber;
			m_flyBehavior(m_flightNumber);
		}
	}

	void Dance()
	{
		if (m_danceBehavior)
		{
			m_danceBehavior();
		}
	}

	virtual void Display() const = 0;

	virtual ~Duck() = default;

private:
	int m_flightNumber = 0;
	FlyBehavior m_flyBehavior;
	QuackBehavior m_quackBehavior;
	DanceBehavior m_danceBehavior;
};

class MallardDuck 
	: public Duck
{
public:
	MallardDuck()
	{
		BehaviorFactory factory;
		SetFlyBehavior(factory.FlyWithWings());
		SetQuackBehavior(factory.QuackQuack());
		SetDanceBehavior(factory.DanceWaltz());
	}

	void Display() const override
	{
		cout << "I'm mallard duck" << endl;
	}
};


class RedheadDuck 
	: public Duck
{
public:
	RedheadDuck()
	{
		BehaviorFactory factory;
		SetFlyBehavior(factory.FlyWithWings());
		SetQuackBehavior(factory.QuackQuack());
		SetDanceBehavior(factory.DanceMinuet());
	}

	void Display() const override
	{
		cout << "I'm redhead duck" << endl;
	}
};

class DecoyDuck 
	: public Duck
{
public:
	void Display() const override
	{
		cout << "I'm deckoy duck" << endl;
	}
};

class RubberDuck 
	: public Duck
{
public:
	RubberDuck()
	{
		BehaviorFactory factory;
		SetQuackBehavior(factory.QuackSqueak());
	}

	void Display() const override
	{
		cout << "I'm rubber duck" << endl;
	}
};

class ModelDuck 
	: public Duck
{
public:
	ModelDuck()
	{
		BehaviorFactory factory;
		SetQuackBehavior(factory.QuackQuack());
	}

	void Display() const override
	{
		cout << "I'm model duck" << endl;
	}
};

