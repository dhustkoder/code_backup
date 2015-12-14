#ifndef WEAPONS_HPP
#define WEAPONS_HPP
#include "weapon.h"
#include "Sword/sword.h"
#include "Axe/axe.h"










inline void Weapon::cast_to_concrete_type() noexcept
{
	switch (m_weaponType)
	{
		case WeaponType::Sword:
			static_cast<Sword*>(this)->cast_to_concrete_type();
			break;
		case WeaponType::Axe:
			static_cast<Axe*>(this)->cast_to_concrete_type();
			break;
		default:
			m_destructorFree = true;
			this->~Weapon();
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
		case WeaponType::Axe:
			return static_cast<Axe*>(this)->attack();
		default:
			printf("attacking with weapon %s", m_name);
			return -1;
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