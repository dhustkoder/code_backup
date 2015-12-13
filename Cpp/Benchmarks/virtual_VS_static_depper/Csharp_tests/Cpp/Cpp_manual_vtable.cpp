#include <iostream>
#include <typeinfo>
#include <vector>

#define LOG(x) std::cout << x << std::endl
//#define DESTRUCTOR_PRINT
						

struct Item
{
	enum class ItemType
	{
		Weapon,
		Consumable
	};
	const ItemType m_type;

	Item(const char* name, ItemType type)
		: m_name(name), m_type(type)
	{
	}

	~Item();
	const char* m_name;
private:
	// this function casts down in hirarchy until the real type of 'this'
	void cast_to_concrete_type() noexcept;

protected:
	bool m_destructorFree = false;

};

// interfaces
struct Weapon : Item
{
	enum class WeaponType
	{
		Sword,
		Axe
	};

	Weapon(const char* name, WeaponType type)
		: Item(name, Item::ItemType::Weapon), m_weaponType(type)
	{
	}

	~Weapon();
	int attack() noexcept;
private:
	friend class Item;
	void cast_to_concrete_type() noexcept;
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
	~Consumable();

private:
	friend class Item;
	void cast_to_concrete_type();
	const ConsumableType m_consumableType;
};





// concrete
struct Sword : Weapon
{
	Sword(const char *name)
		: Weapon(name, Weapon::WeaponType::Sword)
	{
	}

	inline int attack() noexcept
	{
		return 1;
	}


	~Sword()
	{
		asm volatile("" : : "g"(this) : );
#ifdef DESTRUCTOR_PRINT
		printf("D Sword\n");
#endif
		m_destructorFree = true;
	}

private:
	friend class Weapon;

	inline void cast_to_concrete_type() noexcept
	{
		this->~Sword();
	}
};











struct Axe : Weapon
{
	Axe(const char *name)
		: Weapon(name, Weapon::WeaponType::Axe)
	{
	}

	int attack() noexcept
	{
		return 2;
	}

	~Axe()
	{

		asm volatile("" : : "g"(this) : );
#ifdef DESTRUCTOR_PRINT
		printf("D Axe\n");
#endif
		m_destructorFree = true;
	}
private:
	friend class Weapon;
	void cast_to_concrete_type() noexcept
	{
		this->~Axe();
	}
};












struct HealthPotion : Consumable
{
	HealthPotion(const char* name)
		: Consumable(name, ConsumableType::HealthPotion)
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
		asm volatile("" : : "g"(this) : );
		m_destructorFree = true;
	}
private:
	friend class Consumable;
	void cast_to_concrete_type() noexcept
	{
		this->~HealthPotion();
	}

};





struct ManaPotion : Consumable
{
	ManaPotion(const char* name)
		: Consumable(name, ConsumableType::ManaPotion)
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
		asm volatile("" : : "g"(this) : );
		m_destructorFree = true;
	}

private:
	friend class Consumable;
	void cast_to_concrete_type() noexcept
	{
		this->~ManaPotion();
	}
};







// interfaces implementation ( manual vTable )

void Item::cast_to_concrete_type() noexcept
{
	switch (m_type)
	{
	case ItemType::Weapon:
		static_cast<Weapon*>(this)->cast_to_concrete_type();
		return;
	case ItemType::Consumable:
		static_cast<Consumable*>(this)->cast_to_concrete_type();
		return;
	}

}

void Weapon::cast_to_concrete_type() noexcept
{
	switch (m_weaponType)
	{
	case WeaponType::Sword:
		static_cast<Sword*>(this)->cast_to_concrete_type();
		return;
	case WeaponType::Axe:
		static_cast<Axe*>(this)->cast_to_concrete_type();
		return;
	}

}





// interfaces implementation ( manual vTable )
int Weapon::attack() noexcept
{
	switch (m_weaponType)
	{
	case WeaponType::Sword:
		return static_cast<Sword*>(this)->attack();
		break;
	case WeaponType::Axe:
		return static_cast<Axe*>(this)->attack();
		break;
	}
}



void Consumable::cast_to_concrete_type()
{
	switch (m_consumableType)
	{
	case ConsumableType::HealthPotion:
		static_cast<HealthPotion*>(this)->cast_to_concrete_type();
		return;
	case ConsumableType::ManaPotion:
		static_cast<ManaPotion*>(this)->cast_to_concrete_type();
		return;
	default:
		return;
	}
}

int Consumable::consume() noexcept
{

	switch (m_consumableType)
	{
	case ConsumableType::HealthPotion:
		return static_cast<HealthPotion*>(this)->consume();
		break;
	case ConsumableType::ManaPotion:
		return static_cast<ManaPotion*>(this)->consume();
		break;
	}

}


// -----------------------





// Base classes Destructors
Item::~Item()
{
	if (m_destructorFree)
	{
#ifdef DESTRUCTOR_PRINT
		printf("D Item\n");
#endif
		asm volatile("" : : "g"(this) : );  // fake destruction operations.
	}
	else
		this->cast_to_concrete_type();

}

Weapon::~Weapon()
{
	if (m_destructorFree)
	{
#ifdef DESTRUCTOR_PRINT
		printf("D Weapon\n");
#endif
		asm volatile("" : : "g"(this) : );

	}
	else
		this->cast_to_concrete_type();


}


Consumable::~Consumable()
{

	if (m_destructorFree)
	{
#ifdef DESTRUCTOR_PRINT
		printf("D Consumable\n");
#endif
		asm volatile("" : : "g"(this) : );
	}
	else
		this->cast_to_concrete_type();
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
constexpr int maxLoopTest = 1000;
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

	for(int X = 0; X < maxLoopTest; ++X)
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


	//printf("Time Elapsed: %f\n", timer.elapsed());
	//std::cin.ignore();

}


#endif