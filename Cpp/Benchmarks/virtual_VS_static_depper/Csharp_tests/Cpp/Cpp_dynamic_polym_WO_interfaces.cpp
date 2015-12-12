#include <iostream>
#include <typeinfo>
#include <vector>
#include "../timer.h"




// Classes
struct Item
{
	Item(const char* name) : m_name(name)
	{

	}
	virtual ~Item()
	{
		_asm  mov eax, 0x0; // fake destruction operations
	}


	const char* m_name;

};



struct Weapon : Item
{
	Weapon(const char* n) : Item(n) {}
	virtual int attack() const noexcept = 0;
};
struct Consumable : Item
{
	Consumable(const char* n) : Item(n) {}
	virtual int consume() noexcept = 0;
};




// concrete
struct Sword : Weapon
{
	Sword(const char *name) : Weapon(name)
	{

	}

	int attack() const noexcept
	{
		return 1;
	}

	~Sword()
	{
		_asm  mov eax, 0x0;
	}
};


struct Axe : Weapon
{
	Axe(const char *name) : Weapon(name)
	{

	}

	int attack() const noexcept
	{
		return 2;
	}

	~Axe()
	{
		_asm  mov eax, 0x0;
	}


};



struct HealthPotion : Consumable
{
	HealthPotion(const char* name) : Consumable(name)
	{

	}
	~HealthPotion()
	{
		_asm  mov eax, 0x0;
	}

	int consume() noexcept
	{

		return 1;

	}



};

struct ManaPotion : Consumable
{
	ManaPotion(const char* name) : Consumable(name)
	{

	}
	~ManaPotion()
	{
		_asm  mov eax, 0x0;
	}

	int consume() noexcept
	{
		return 2;
	}



};

// user code
constexpr int maxItems = 1000000;
constexpr int maxLoopIterations = 1000;
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


	Weapon *is_weapon;
	Consumable *is_consumable;

	for (auto ptr : vec)
	{
		if ((is_weapon = dynamic_cast<Weapon*>(ptr)))
			(is_weapon->attack() == 1) ? ++swords : ++axes;
		else if ((is_consumable = dynamic_cast<Consumable*>(ptr)))
			(is_consumable->consume() == 1) ? ++healthPotions : ++manaPotions;
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

	for (int X = 0; X < maxLoopIterations; ++X)
	{

		for (int i = 0; i < static_div<maxItems, 2>::value; ++i)
			itemList.push_back((i % 2 == 0) ? (Item*)new Sword("Excalibur") : (Axe*) new Axe("Horned Axe"));

		for (int i = 0; i < static_div<maxItems, 2>::value; ++i)
			itemList.push_back((i % 2 == 0) ? (Item*)new HealthPotion("Elixir") : (Axe*) new ManaPotion("Ether"));

		useAllItems(itemList);

		for (auto ptr : itemList)
			delete ptr;

		itemList.clear();
	}


}