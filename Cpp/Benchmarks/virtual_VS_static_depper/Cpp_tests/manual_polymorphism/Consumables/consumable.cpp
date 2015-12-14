#ifndef CONSUMABLES_HPP
#define CONSUMABLES_HPP
#include "consumable.h"
#include "ManaPotion/mana_potion.h"
#include "HealthPotion/health_potion.h"




void Consumable::cast_to_concrete_type() noexcept
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

// interface ...
int Consumable::consume() noexcept
{

	switch (m_consumableType)
	{
		case ConsumableType::HealthPotion:
			return static_cast<HealthPotion*>(this)->consume();
		case ConsumableType::ManaPotion:
			return static_cast<ManaPotion*>(this)->consume();
		default:
			return -1;
	}

}


Consumable::~Consumable()
{

	if (m_destructorFree)
	{
#ifdef DESTRUCTOR_PRINT
		printf("D Consumable\n");
#endif
		asm volatile( "" : : "g"(this) : );
	}
	else
		this->cast_to_concrete_type();
}



#endif