#pragma once

class Duck
{
public:	

	void SetFlyBehavior(unique_ptr<IFlyBehavior>&& flyBehavior)
	{
		m_flyBehavior = move(flyBehavior);
	}

	void SetQuackBehavior(unique_ptr<IQuackBehavior>&& quackBehavior)
	{
		m_quackBehavior = move(quackBehavior);
	}

	void SetDanceBehavior(unique_ptr<IDanceBehavior>&& danceBehavior)
	{
		m_danceBehavior = move(danceBehavior);
	}

	void Quack() const
	{
		if (m_quackBehavior)
		{
			m_quackBehavior->Quack();
		}
	}

	void Fly()
	{
		if (m_flyBehavior)
		{
			++m_flightNumber;
			m_flyBehavior->Fly(m_flightNumber);
		}		
	}

	void Dance()
	{
		if (m_danceBehavior)
		{
			m_danceBehavior->Dance();
		}
	}
	
	virtual void Display() const = 0;

	virtual ~Duck() = default;

private:
	int m_flightNumber = 0;
	unique_ptr<IFlyBehavior> m_flyBehavior;
	unique_ptr<IQuackBehavior> m_quackBehavior;
	unique_ptr<IDanceBehavior> m_danceBehavior;
};

class MallardDuck : public Duck
{
public:
	MallardDuck()		
	{
		SetFlyBehavior(make_unique<FlyWithWings>());
		SetQuackBehavior(make_unique<QuackBehavior>());
		SetDanceBehavior(make_unique<WaltzDanceBehavior>());
	}

	void Display() const override
	{
		cout << "I'm mallard duck" << endl;
	}
};

class RedheadDuck : public Duck
{
public:
	RedheadDuck()		
	{
		SetFlyBehavior(make_unique<FlyWithWings>());
		SetQuackBehavior(make_unique<QuackBehavior>());
		SetDanceBehavior(make_unique<MinuetDanceBehavior>());
	}

	void Display() const override
	{
		cout << "I'm redhead duck" << endl;
	}
};

class DecoyDuck : public Duck
{
public:	
	void Display() const override
	{
		cout << "I'm deckoy duck" << endl;
	}
};

class RubberDuck : public Duck
{
public:
	RubberDuck()		
	{
		SetQuackBehavior(make_unique<SqueakBehavior>());
	}

	void Display() const override
	{
		cout << "I'm rubber duck" << endl;
	}	
};

class ModelDuck : public Duck
{
public:
	ModelDuck()		
	{
		SetQuackBehavior(make_unique<QuackBehavior>());
	}

	void Display() const override
	{
		cout << "I'm model duck" << endl;
	}	
};
