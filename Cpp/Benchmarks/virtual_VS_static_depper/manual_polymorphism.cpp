#include <iostream>
#include <typeinfo>
#include <vector>
#include "timer.h"
#define LOG(x) std::cout << x << std::endl
//#define DESTRUCTOR_PRINT
						


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
		_asm  mov eax, 0x0;
#ifdef DESTRUCTOR_PRINT
		printf("D Sword\n");
#endif
		m_destructorFree = false;
		
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

		_asm  mov eax, 0x0;
#ifdef DESTRUCTOR_PRINT
		printf("D Axe\n");
#endif
		m_destructorFree = false;
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
		#ifdef DESTRUCTOR_PRINT
		printf("D HealthPotion\n");
		#endif
		_asm  mov eax, 0x0;
		m_destructorFree = false;
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
		#ifdef DESTRUCTOR_PRINT
		printf("D ManaPotion\n");
		#endif
		_asm  mov eax, 0x0;
		m_destructorFree = false;
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


// Base classes Destructors
Item::~Item()
{ 
	if (m_destructorFree)
	{
		#ifdef DESTRUCTOR_PRINT
		printf("D Item\n");
		#endif
		_asm  mov eax, 0x0;  // fake destruction operations.

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
				return;
		}
		
		
	} 

}


Weapon::~Weapon()
{

	if (m_destructorFree)
	{
		#ifdef DESTRUCTOR_PRINT
		printf("D Weapon\n");
		#endif
		_asm  mov eax, 0x0;
	
		switch(m_weaponType)
		{
			case WeaponType::Sword:
				static_cast<Sword*>(this)->~Sword();
				return;
			case WeaponType::Axe:
				static_cast<Axe*>(this)->~Axe();
				return;
			default:
				m_destructorFree = false;
				return;
		}
		
		
	} 

}



Consumable::~Consumable()
{
	
	if (m_destructorFree)
	{
		#ifdef DESTRUCTOR_PRINT
		printf("D Consumable\n");
		#endif
		_asm  mov eax, 0x0;
	
		switch(m_consumableType)
		{
			case ConsumableType::HealthPotion:
				static_cast<HealthPotion*>(this)->~HealthPotion();
				return;
			case ConsumableType::ManaPotion:
				static_cast<ManaPotion*>(this)->~ManaPotion();
				return;
			default:
				m_destructorFree = false;
				return;
		}
		
		
	} 
}





// user code

#ifdef DESTRUCTOR_PRINT

// Destructor calls tests
int main() 
{

	
	Item *item = new Sword("Excalibur");
	Item *item2 = new HealthPotion("elixir");


	delete item;
	
	delete item2;

	Item *item3 = new Axe("Horned Axe");


	Item *item4 = new ManaPotion("Ether");

	delete item3;
	delete item4;


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

	for (auto &ptr : vec)
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