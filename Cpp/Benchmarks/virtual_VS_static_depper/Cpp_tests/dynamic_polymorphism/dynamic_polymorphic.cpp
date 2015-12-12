#include <iostream>
#include <typeinfo>
#include <vector>
#include "../timer.h"

// Interfaces
struct IWeapon
{
	virtual int attack() const noexcept = 0;
};
struct IConsumable
{
	virtual int consume() noexcept = 0;
};



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







// concrete
struct Sword : Item, IWeapon
{
	Sword(const char *name) : Item(name)
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


struct Axe : Item, IWeapon
{
	Axe(const char *name) : Item(name)
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



struct HealthPotion : Item, IConsumable
{
	HealthPotion(const char* name) : Item(name)
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

struct ManaPotion : Item, IConsumable
{
	ManaPotion(const char* name) : Item(name)
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
	int manaPotions= 0;

	
	IWeapon *is_weapon;
	IConsumable *is_consumable;
	
	for(auto ptr : vec)
	{
		if((is_weapon = dynamic_cast<IWeapon*>(ptr)))
			( is_weapon->attack() == 1 ) ? ++swords : ++axes;
		else if((is_consumable = dynamic_cast<IConsumable*>(ptr)))
			( is_consumable->consume() == 1) ? ++healthPotions : ++manaPotions;
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
	for(int i = 0; i < static_div<maxItems, 2>::value ; ++i)
		itemList.push_back((i % 2 == 0) ? (Item*)new Sword("Excalibur") : (Axe*) new Axe("Horned Axe"));
		
	for(int i = 0; i < static_div<maxItems, 2>::value ; ++i)
		itemList.push_back((i % 2 == 0) ? (Item*)new HealthPotion("Elixir") : (Axe*) new ManaPotion("Ether"));
	
	
	useAllItems(itemList);

	for(auto ptr : itemList)
		delete ptr;

	printf("Time Elapsed: %f\n", timer.elapsed());
	std::cin.ignore();
	


}
