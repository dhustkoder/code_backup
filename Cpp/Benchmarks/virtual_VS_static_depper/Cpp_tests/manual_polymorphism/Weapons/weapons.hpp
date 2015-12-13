#ifndef WEAPONS_HPP
#define WEAPONS_HPP
#include "../item.h"

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











#include "Sword/sword.h"
#include "Axe/axe.h"










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





Weapon::~Weapon()
{
	if (m_destructorFree)
	{
#ifdef DESTRUCTOR_PRINT
		printf("D Weapon\n");
#endif
		asm volatile( "" : : "g"(this) : );

	}
	else
		this->cast_to_concrete_type();


}

#endif