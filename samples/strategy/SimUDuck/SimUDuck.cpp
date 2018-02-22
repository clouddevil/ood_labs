#include <cassert>
#include <iostream>
#include <memory>
#include <vector>
#include <functional>

using namespace std;

namespace l1
{

#include "DanceBehavior.h"
#include "FlyBehavior.h"
#include "QuackBehavior.h"
#include "Ducks.h"

}

namespace l3
{

#include "DucksFunc.h"

}

template<typename Duck>
void PlayWithDuck(Duck& duck)
{
	duck.Display();
	duck.Quack();
	duck.Fly();
	duck.Dance();
	cout << endl;
}

void main()
{
	using namespace l3;

	MallardDuck mallarDuck;
	PlayWithDuck(mallarDuck);

	RedheadDuck redheadDuck;
	PlayWithDuck(redheadDuck);
	PlayWithDuck(redheadDuck);
	PlayWithDuck(redheadDuck);

	RubberDuck rubberDuck;
	PlayWithDuck(rubberDuck);

	DecoyDuck deckoyDuck;
	PlayWithDuck(deckoyDuck);

	ModelDuck modelDuck;
	PlayWithDuck(modelDuck);	
}
