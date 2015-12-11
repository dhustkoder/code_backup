#include <iostream>
#include <typeinfo>
#include <boost/container/vector.hpp>
#include "timer.h"
#define LOG(x) std::cout << x << std::endl


struct Item
{
	Item(const char* name) : m_name(name)
	{
	
	}
	
	virtual ~Item()
	{ 
		asm volatile("" : : "g"(this) : );


	}
	
	
	const char* m_name;

};


// interfaces
struct Weapon : Item
{

	Weapon(const char* name) : Item(name)
	{
	
	}
	virtual ~Weapon()
	{ 
		asm volatile("" : : "g"(this) : );


	}
	
	virtual int attack() noexcept = 0;
};



struct Consumable : Item
{

	Consumable(const char* name) : Item(name)
	{
		
	}
	
	
	virtual int consume() noexcept = 0;
	
	virtual ~Consumable()
	{ 
		asm volatile("" : : "g"(this) : );


	}

};





// concrete
struct Sword : Weapon
{
	Sword(const char *name) : Weapon(name)
	{
		
	}
	
	int attack() noexcept
	{
		return 1;
	}
	
	~Sword() 
	{
		asm volatile("" : : "g"(this) : ); 
		
	}
};


struct Axe : Weapon
{
	Axe(const char *name) : Weapon(name)
	{
		
	}
	
	int attack() noexcept
	{
		return 2;
	}
	
	~Axe() 
	{
		asm volatile("" : : "g"(this) : );
	}
};



struct HealthPotion : Consumable
{
	HealthPotion(const char* name) : Consumable(name)
	{
	
	}
	
	int consume() noexcept
	{
	
		return 1;
	
	}
	
	~HealthPotion()
	{
		asm volatile("" : : "g"(this) : );
	}

};

struct ManaPotion : Consumable
{
	ManaPotion(const char* name) : Consumable(name)
	{
	
	}
	
	int consume() noexcept
	{
	
		return 2;
		
	
	}
	
	~ManaPotion()
	{
		asm volatile("" : : "g"(this) : );
	}

};

	

// user code
constexpr int maxItems = 1000000;
template<int x, int n>
struct static_div
{
	static constexpr int value = x / n;
};



void useAllItems(boost::container::vector<Item*> &vec)
{
	int swords = 0;
	int axes = 0;
	int healthPotions = 0;
	int manaPotions= 0;

	
	Weapon *is_weapon;
	Consumable *is_consumable;
	
	for(auto &ptr : vec)
	{
		if((is_weapon = dynamic_cast<Weapon*>(ptr)))
			( is_weapon->attack() == 1 ) ? ++swords : ++axes;
		else if((is_consumable = dynamic_cast<Consumable*>(ptr)))
			( is_consumable->consume() == 1) ? ++healthPotions : ++manaPotions;
	}

		
	
	printf("Swords in list: %i\n", swords);
	printf("Axes in list: %i\n", axes);
	printf("HealthPotions in list: %i\n", healthPotions);
	printf("ManaPotions in list: %i\n", manaPotions);
	

}



int main()
{
	boost::container::vector<Item*> itemList;
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
	
	


}
