#pragma once


struct IFlyBehavior
{
	virtual ~IFlyBehavior() {};
	virtual void Fly(int flightNumber) = 0;
};

class FlyWithWings 
	: public IFlyBehavior
{
public:
	void Fly(int flightNumber) override
	{
		cout << "I'm flying " << flightNumber << " with wings!!" << endl;
	}
};
