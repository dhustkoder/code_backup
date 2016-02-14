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

	Item(const char* name, ItemType type) : m_name(name), m_type(type)
	{
	
	}
	
	
	~Item();
	
	
	const char* m_name;
	const ItemType m_type;
	bool m_destructorCastFree = true;
	bool m_destructorFree = true;

};


// interfaces
struct Weapon : Item
{
	enum class WeaponType
	{
		Sword,
		Axe
	};


	Weapon(const char* name,WeaponType type) : Item(name, Item::ItemType::Weapon), m_weaponType(type)
	{
	
	}
	~Weapon();
	
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

	Consumable(const char* name, ConsumableType type) : Item(name, ItemType::Consumable), m_consumableType(type)
	{
		
	}
	
	
	int consume() noexcept;
	
	~Consumable();
	
	const ConsumableType m_consumableType;
};





// concrete
struct Sword : Weapon
{
	Sword(const char *name) : Weapon(name, Weapon::WeaponType::Sword)
	{
		
	}
	
	int attack() noexcept
	{
		return 1;
	}
	
	~Sword() 
	{
		asm volatile("" : : "g"(this) : ); 
		m_destructorFree = false;
		m_destructorCastFree = false;
		
	}
};


struct Axe : Weapon
{
	Axe(const char *name) : Weapon(name, Weapon::WeaponType::Axe)
	{
		
	}
	
	int attack() noexcept
	{
		return 2;
	}
	
	~Axe() 
	{
		asm volatile("" : : "g"(this) : );
		m_destructorFree = false;
		m_destructorCastFree = false;
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
		m_destructorFree = false;
		m_destructorCastFree = false;
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
		m_destructorFree = false;
		m_destructorCastFree = false;
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


	
Item::~Item()
{ 
	if(m_destructorFree)
		asm volatile("" : : "g"(this) : );
	


	if(m_destructorCastFree)
	{ 
		switch(m_type)
		{
			case ItemType::Weapon:
				static_cast<Weapon*>(this)->~Weapon();
				return;
			case ItemType::Consumable:
				static_cast<Consumable*>(this)->~Consumable();
				return;
			default:
				// as this is the base of ALL  Items it can save time and jump directly.
				break;
		}
		
		
	} 

}

Weapon::~Weapon()
{

	if(m_destructorFree)
		asm volatile("" : : "g"(this) : );
	

		
	if(m_destructorCastFree)
	{ 
		switch(m_weaponType)
		{
			case WeaponType::Sword:
				static_cast<Sword*>(this)->~Sword();
				return;
			case WeaponType::Axe:
				static_cast<Axe*>(this)->~Axe();
				return;
			default:
				m_destructorCastFree = false;
				m_destructorFree = false;
				break;
		}
		
		
	} 

}



Consumable::~Consumable()
{
	
	if(m_destructorFree)
		asm volatile("" : : "g"(this) : );
	
	
		
	if(m_destructorCastFree)
	{ 
		switch(m_consumableType)
		{
			case ConsumableType::HealthPotion:
				static_cast<HealthPotion*>(this)->~HealthPotion();
				return;
			case ConsumableType::ManaPotion:
				static_cast<ManaPotion*>(this)->~ManaPotion();
				return;
			default:
				m_destructorCastFree = false;
				m_destructorFree = false;
				break;
		}
		
		
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
	Timer timer;
	int swords = 0;
	int axes = 0;
	int healthPotions = 0;
	int manaPotions= 0;
	timer.start();
	for(auto &ptr : vec)
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
	for(auto ptr : vec)
		delete ptr;

	double timeElapsed = timer.elapsed();
	printf("Swords in list: %i\n", swords);
	printf("Axes in list: %i\n", axes);
	printf("HealthPotions in list: %i\n", healthPotions);
	printf("ManaPotions in list: %i\n", manaPotions);
	printf("Time Elapsed: %f\n", timeElapsed);

}



int main()
{
	boost::container::vector<Item*> itemList;
	itemList.reserve(maxItems);
	
	for(int i = 0; i < static_div<maxItems, 2>::value ; ++i)
		itemList.push_back((i % 2 == 0) ? (Item*)new Sword("Excalibur") : (Axe*) new Axe("Horned Axe"));
		
	for(int i = 0; i < static_div<maxItems, 2>::value ; ++i)
		itemList.push_back((i % 2 == 0) ? (Item*)new HealthPotion("Elixir") : (Axe*) new ManaPotion("Ether"));
	
	
	useAllItems(itemList);
	
	

	


}
