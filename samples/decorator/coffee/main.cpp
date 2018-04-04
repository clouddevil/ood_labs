#include "Beverages.h"
#include "Condiments.h"

#include <iostream>
#include <string>
#include <functional>

using namespace std;


/*
Функциональный объект, создающий лимонную добавку
*/
struct MakeLemon
{
	MakeLemon(unsigned quantity)
		:m_quantity(quantity)
	{}

	auto operator()(IBeveragePtr && beverage)const
	{
		return make_unique<CLemon>(move(beverage), m_quantity); 
	}
private:
	unsigned m_quantity;
};

/*
Функция, возвращающая функцию, создающую коричную добавку
*/
function<IBeveragePtr(IBeveragePtr &&)> MakeCinnamon()
{
	return [] (IBeveragePtr && b) {
		return make_unique<CCinnamon>(move(b));
	};
}

/*
Возвращает функцию, декорирующую напиток определенной добавкой

Параметры шаблона: 
	Condiment - класс добавки, конструктор которого в качестве первого аргумента
				принимает IBeveragePtr&& оборачиваемого напитка
	Args - список типов прочих параметров конструктора (возможно, пустой)
*/
template <typename Condiment, typename... Args>
auto MakeCondiment(const Args&...args)
{
	// Возвращаем функцию, декорирующую напиток, переданный ей в качестве аргумента
	// Дополнительные аргументы декоратора, захваченные лямбда-функцией, передаются
	// конструктору декоратора через make_unique
	return [=](auto && b) {
		// Функции make_unique передаем b вместе со списком аргументов внешней функции
		return make_unique<Condiment>(forward<decltype(b)>(b), args...);
	};
}

/*
Перегруженная версия оператора <<, которая предоставляет нам синтаксический сахар
для декорирования компонента

Позволяет создать цепочку оборачивающих напиток декораторов следующим образом:
auto beverage = make_unique<CConcreteBeverage>(a, b, c)
					<< MakeCondimentA(d, e, f)
					<< MakeCondimentB(g, h);

Функциональные объекты MakeCondiment* запоминают аргументы, необходимые для создания
дополнения, и возвращают фабричную функцию, принимающую оборачиваемый напиток, которая
при своем вызове создаст нужный объект Condiment, передав ему запомненные аргументы.
Использование:
	auto beverage = 
		make_unique<CConcreteBeverage>(a, b, c)
		<< MakeCondimentA(d, e, f)
		<< MakeCondimentB(g, h);
или даже так:
	auto beverage = 
		make_unique<CConcreteBeverage>
		<< MakeCondiment<CondimentA>(d, e, f)
		<< MakeCondiment<CondimentB>(g, h);
В последнем случае нет необходимости писать вручную реализации MakeCondimentA и MakeCondimentB, т.к.
необходимую реализацию сгенерирует компилятор

Классический способ оборачивания выглядел бы так:
	auto baseBeverage = make_unique<CConcretedBeverage>(a, b, c);
	auto wrappedWithCondimentA = make_unique<CCondimentA>(move(baseBeverage), d, e, f);
	auto beverage = make_unique<CCondimentB>(move(wrappedWithCondimentA), g, h);
либо так:
	auto beverage = make_unique<CCondimentB>(
						make_unique<CCondimentA>(
							make_unique<CConcreteBeverage>(a, b, c), // Напиток
							d, e, f	// доп. параметы CondimentA
						),
						g, h		// доп. параметры CondimentB
					);

unique_ptr<CLemon> operator << (IBeveragePtr && lhs, const MakeLemon & factory)
{
	return factory(move(lhs));
}
unique_ptr<CCinnamon> operator << (IBeveragePtr && lhs, const MakeCinnamon & factory)
{
	return factory(move(lhs));
}
*/
template <typename Component, typename Decorator>
auto operator << (Component && component, const Decorator & decorate)
{
	return decorate(forward<Component>(component));
}

int BeverageChoice()
{
	cout << "1 - Coffee; 2 - Tea; 3 - Milkshake;" << endl;

	int beverageChoice = 0;
	cin >> beverageChoice;
	return beverageChoice;
}

int CondimentChoice()
{
	cout << "1 - No Condiment; 2 - Lemon; 3 - Cinnamon; 4 - Chocolate; 5 - Liquor; 6 - Cream;" << endl;

	int condimentChoice;
	cin >> condimentChoice;	
	return condimentChoice;
}

int CondimentQuantity(std::string condimentName, int maxQuantity)
{
	cout << condimentName << " Quantity (max: " << maxQuantity << ")" << endl;

	int condimentQuantity = 0;
	cin >> condimentQuantity;
	return clamp(condimentQuantity, 0, maxQuantity);
}

auto CondimentLiquorType()
{
	cout << "1 - Сhocolate; 5 - Nuts;" << endl;

	int liquorType = 0;
	cin >> liquorType;
	return (liquorType == 1) ? LiquorType::Chocolate : LiquorType::Nuts;
}

IBeveragePtr MakeCoffee()
{
	cout << "1 - Capuccino; 2 - Latte;" << endl;
	
	int beverageChoice = 0;
	cin >> beverageChoice;

	cout << "1 - Standard; 2 - Double;" << endl;

	int beverageQuantity = 0;
	cin >> beverageQuantity;

	if (beverageChoice == 1)
	{
		return std::make_unique<CCapuccino>(beverageQuantity);
	}
	else  if (beverageChoice == 2)
	{
		return std::make_unique<CLatte>(beverageQuantity);
	}
	return nullptr;
}

IBeveragePtr MakeTea()
{
	std::string tea[] = {"Black", "Green", "White", "Herbal"};

	unsigned index = 1;
	for (auto&& t : tea)
	{
		cout << index++ << " - " << t  << "; ";		
	}
	cout << endl;
		
	cin >> index;

	if ((index > 0) && (index <= std::size(tea)))
	{
		auto teaType = tea[index - 1];
		return std::make_unique<CTea>(teaType);
	}
	return nullptr;
}

IBeveragePtr MakeMilkshake()
{
	cout << "1 - Small; 2 - Middle; 3 - Large;" << endl;
	int shakeSize = 0;
	cin >> shakeSize;
	if ((0 < shakeSize) && (shakeSize <= 3))
	{
		return std::make_unique<CMilkshake>(shakeSize);
	}
	return nullptr;	
}

IBeveragePtr MakeBeverage(int choice)
{
	switch (choice)
	{
	case 1:
		return MakeCoffee();
	case 2:
		return MakeTea();
	case 3:
		return MakeMilkshake();
	default:
		return nullptr;
	}
}


bool DialogWithUser()
{
	const int choice = BeverageChoice();
	if (choice == 0)
	{
		return false;
	}

	auto beverage = MakeBeverage(choice);
	if (!beverage)
	{
		return true;
	}	

	do
	{
		const int condimentChoice = CondimentChoice();
		if (condimentChoice == 0)
		{
			return true;
		}
		else if (condimentChoice == 1)
		{
			break;
		}
		else if (condimentChoice == 2)
		{
			const int condimentQuantity = CondimentQuantity("Lemon", 2);
			if (condimentQuantity > 0)
			{
				beverage = move(beverage) << MakeCondiment<CLemon>(condimentQuantity);
			}			
		}
		else if (condimentChoice == 3)
		{
			beverage = move(beverage) << MakeCondiment<CCinnamon>();
		}
		else if (condimentChoice == 4)
		{
			const int condimentQuantity = CondimentQuantity("Chocolate", 5);
			if (condimentQuantity > 0)
			{
				beverage = move(beverage) << MakeCondiment<CChocolate>(condimentQuantity);
			}
		}
		else if (condimentChoice == 5)
		{
			auto liquorType = CondimentLiquorType();
			beverage = move(beverage) << MakeCondiment<CLiquor>(liquorType);
		}
		else if (condimentChoice == 6)
		{
			beverage = move(beverage) << MakeCondiment<CCream>();
		}

	} while (true);

	cout << "*************************************************************" << endl;
	cout << beverage->GetDescription() << ", cost: " << beverage->GetCost() << endl;
	cout << "*************************************************************" << endl;

	return true;
}


int main()
{
	while (DialogWithUser())
	{
		// ok
		cout << endl;
	}

#if 0
	{
		// Наливаем чашечку латте
		auto latte = make_unique<CLatte>();
		// добавляем корицы
		auto cinnamon = make_unique<CCinnamon>(move(latte));
		// добавляем пару долек лимона
		auto lemon = make_unique<CLemon>(move(cinnamon), 2);
		// добавляем пару кубиков льда
		auto iceCubes = make_unique<CIceCubes>(move(lemon), 2, IceCubeType::Dry);
		// добавляем 2 грамма шоколадной крошки
		auto beverage = make_unique<CChocolateCrumbs>(move(iceCubes), 2);

		// Выписываем счет покупателю
		cout << beverage->GetDescription() << " costs " << beverage->GetCost() << endl;
	}

	{
		auto beverage =
			make_unique<CChocolateCrumbs>(			// Внешний слой: шоколадная крошка
				make_unique<CIceCubes>(				// | под нею - кубики льда
					make_unique<CLemon>(			// | | еще ниже лимон
						make_unique<CCinnamon>(		// | | | слоем ниже - корица
							make_unique<CLatte>()),	// | | |   в самом сердце - Латте
						2),							// | | 2 дольки лимона
					2, IceCubeType::Dry),			// | 2 кубика сухого льда
				2);									// 2 грамма шоколадной крошки

		// Выписываем счет покупателю
		cout << beverage->GetDescription() << " costs " << beverage->GetCost() << endl;
	}

	// Подробнее рассмотрим работу MakeCondiment и оператора <<
	{
		// lemon - функция, добавляющая "2 дольки лимона" к любому напитку
		auto lemon2 = MakeCondiment<CLemon>(2);
		// iceCubes - функция, добавляющая "3 кусочка льда" к любому напитку
		auto iceCubes3 = MakeCondiment<CIceCubes>(3, IceCubeType::Water);
		
		auto tea = make_unique<CTea>();

		// декорируем чай двумя дольками лимона и тремя кусочками льда
		auto lemonIceTea = iceCubes3(lemon2(move(tea)));	
		/* Предыдущая строка выполняет те же действия, что и следующий код:
		auto lemonIceTea = 
			make_unique<CIceCubes>(
				make_unique<CLemon>(
					move(tea), 
					2), 
				2, IceCubeType::Water);
		*/
		
		auto oneMoreLemonIceTea =
			make_unique<CTea>()	// Берем чай
			<< MakeCondiment<CLemon>(2)	// добавляем пару долек лимона
			<< MakeCondiment<CIceCubes>(3, IceCubeType::Water); // и 3 кубика льда
		/*
		Предыдущая конструкция делает то же самое, что и следующая:
		auto oneMoreLemonIceTea =
			MakeCondiment<CIceCubes>(3, IceCubeType::Water)(
				MakeCondiment<CLemon>(2)(make_unique<CTea>())
				);
		*/
	}

	// Аналог предыдущего решения с добавкой синтаксического сахара
	// обеспечиваемого операторами << и функцией MakeCondiment
	{
		auto beverage = 
			make_unique<CLatte>()							// Наливаем чашечку латте,
			<< MakeCondiment<CCinnamon>()					// оборачиваем корицей,
			<< MakeCondiment<CLemon>(2)						// добавляем пару долек лимона
			<< MakeCondiment<CIceCubes>(2, IceCubeType::Dry)// брасаем пару кубиков сухого льда
			<< MakeCondiment<CChocolateCrumbs>(2);			// посыпаем шоколадной крошкой

		// Выписываем счет покупателю
		cout << beverage->GetDescription() << " costs " << beverage->GetCost() << endl;
	}

	{
		auto beverage = 
			make_unique<CMilkshake>()					// Наливаем молочный коктейль
			<< MakeCondiment<CSyrup>(SyrupType::Maple)	// заливаем кленовым сиропом
			<< MakeCondiment<CCoconutFlakes>(8);		// посыпаем кокосовой стружкой

		// Выписываем счет покупателю
		cout << beverage->GetDescription() << " costs " << beverage->GetCost() << endl;
	}
#endif

}
