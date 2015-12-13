#ifndef CONSUMABLES_HPP
#define CONSUMABLES_HPP
#include "../item.h"

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




#include "ManaPotion/mana_potion.h"
#include "HealthPotion/health_potion.h"




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

// interface ...
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