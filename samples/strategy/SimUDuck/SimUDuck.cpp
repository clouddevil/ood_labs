#include <cassert>
#include <iostream>
#include <memory>
#include <vector>

using namespace std;

#include "DanceBehavior.h"
#include "FlyBehavior.h"
#include "QuackBehavior.h"
#include "Ducks.h"

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
