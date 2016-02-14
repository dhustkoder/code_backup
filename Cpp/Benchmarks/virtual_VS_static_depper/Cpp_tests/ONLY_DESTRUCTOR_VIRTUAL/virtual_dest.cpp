#include <iostream>
#include <typeinfo>
#include <boost/container/vector.hpp>
#include "timer.h"
#define LOG(x) std::cout << x << std::endl


struct Item
{
	enum class ItemType
	{
		Weapon,
		Consumable,
		Wearable
	};

	Item(const char* name, ItemType type) 
		: m_name(name), m_type(type)
	{
	
	}
	
	
	virtual ~Item()
	{
		asm volatile("" : : "g"(this) : ); 

	}
	
	
	const char* m_name;
	const ItemType m_type;

};


// interfaces
struct Weapon : Item
{
	enum class WeaponType
	{
		Sword,
		Axe
	};

	Weapon(const char* name,WeaponType type) 
		: Item(name, Item::ItemType::Weapon), m_weaponType(type)
	{
	
	}
	~Weapon()
	{
		asm volatile("" : : "g"(this) : ); 
	}
	
	int attack() noexcept;
	const WeaponType m_weaponType;
};



struct Consumable : Item
{
	enum class ConsumableType
	{
		HealthPotion,
		ManaPotion
	};

	Consumable(const char* name, ConsumableType type) 
		: Item(name, ItemType::Consumable), m_consumableType(type)
	{
		
	}
	
	
	int consume() noexcept;
	
	~Consumable()
	{
		asm volatile("" : : "g"(this) : ); 
	}
	
	const ConsumableType m_consumableType;
};





// concrete
struct Sword : Weapon
{
	Sword(const char *name) : Weapon(name, Weapon::WeaponType::Sword)
	{
		
	}
	
	int attack() const noexcept
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
	Axe(const char *name) : Weapon(name, Weapon::WeaponType::Axe)
	{
		
	}
	
	int attack() const noexcept
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
	HealthPotion(const char* name) : Consumable(name, ConsumableType::HealthPotion)
	{
	
	}
	
	int consume() const noexcept
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
	ManaPotion(const char* name) : Consumable(name, ConsumableType::ManaPotion)
	{
	
	}
	
	int consume() const noexcept
	{
	
		return 2;
		
	
	}
	
	~ManaPotion()
	{
		asm volatile("" : : "g"(this) : );
	}

};






// interfaces implementation ( manual vTable )
int Weapon::attack() noexcept
{
	switch(m_weaponType)
	{
		case WeaponType::Sword:
			return static_cast<Sword*>(this)->attack();
			break;
		case WeaponType::Axe:
			return static_cast<Axe*>(this)->attack();
			break;
	}
}


int Consumable::consume() noexcept
{

	switch(m_consumableType)
	{
		case ConsumableType::HealthPotion:
			return static_cast<HealthPotion*>(this)->consume();
			break;
		case ConsumableType::ManaPotion:
			return static_cast<ManaPotion*>(this)->consume();
			break;
	}

}





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


	for(auto ptr : vec)
	{
		switch(ptr->m_type)
		{
			case Item::ItemType::Weapon:
				(static_cast<Weapon*>(ptr)->attack() == 1) ? ++swords : ++axes ;
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
	Timer timer;
	timer.start();
	boost::container::vector<Item*> itemList;
	itemList.reserve(maxItems);
	
	for(int i = 0; i < static_div<maxItems, 2>::value ; ++i)
		itemList.push_back((i % 2 == 0) ? (Item*)new Sword("Excalibur") : (Axe*) new Axe("Horned Axe"));
		
	for(int i = 0; i < static_div<maxItems, 2>::value ; ++i)
		itemList.push_back((i % 2 == 0) ? (Item*)new HealthPotion("Elixir") : (Axe*) new ManaPotion("Ether"));
	
	
	useAllItems(itemList);
	for(auto ptr : itemList)
		delete ptr;
	
	double timeElapsed = timer.elapsed();
	printf("Time Elapsed: %f\n", timeElapsed);
	
	


}
