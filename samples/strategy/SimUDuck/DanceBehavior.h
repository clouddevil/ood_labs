#pragma once


struct IDanceBehavior
{
	virtual ~IDanceBehavior() = default;
	virtual void Dance() = 0;
};


class WaltzDanceBehavior 
	: public IDanceBehavior
{
public:
	void Dance() override
	{
		cout << "Dancing waltz" << endl;
	}
};

class MinuetDanceBehavior
	: public IDanceBehavior
{
public:
	void Dance() override
	{
		cout << "Dancing minuet" << endl;
	}
};
