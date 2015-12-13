#include <iostream>
#include <vector>
#include "../timer.h"
#define LOG(x) std::cout << x << std::endl

#include "Weapons/weapons.hpp"
#include "Consumables/consumables.hpp"
// user code

#ifdef DESTRUCTOR_PRINT

// Destructor calls tests
int main() 
{

	
	Item *item = new Sword("Excalibur");
	//Item *item2 = new HealthPotion("elixir");

	//Weapon *weapon = (Weapon*)item;

	//delete weapon;
	
	delete item;

}


#else

// Speed Test

constexpr int maxItems = 1000000;
template<int x, int n>
struct static_div
{
	static constexpr int value = x / n;
};



void useAllItems(std::vector<Item*> &vec)
{

	int swords = 0;
	int axes = 0;
	int healthPotions = 0;
	int manaPotions = 0;

	for (auto ptr : vec)
	{
		switch (ptr->m_type)
		{
			case Item::ItemType::Weapon:
				(static_cast<Weapon*>(ptr)->attack() == 1) ? ++swords : ++axes;
				break;
			case Item::ItemType::Consumable:
				(static_cast<Consumable*>(ptr)->consume() == 1) ? ++healthPotions : ++manaPotions;
			default:
				break;
		}
	}

	printf("Swords in list: %i\n", swords);
	printf("Axes in list: %i\n", axes);
	printf("HealthPotions in list: %i\n", healthPotions);
	printf("ManaPotions in list: %i\n", manaPotions);

}



int main()
{
	std::vector<Item*> itemList;
	itemList.reserve(maxItems);
	Timer timer;
	timer.start();
	for (int i = 0; i < static_div<maxItems, 2>::value; ++i)
		itemList.push_back((i % 2 == 0) ? (Item*)new Sword("Excalibur") : (Axe*) new Axe("Horned Axe"));

	for (int i = 0; i < static_div<maxItems, 2>::value; ++i)
		itemList.push_back((i % 2 == 0) ? (Item*)new HealthPotion("Elixir") : (Axe*) new ManaPotion("Ether"));


	useAllItems(itemList);


	for (auto ptr : itemList)
		delete ptr;

	printf("Time Elapsed: %f\n", timer.elapsed());
	std::cin.ignore();

}


#endif
