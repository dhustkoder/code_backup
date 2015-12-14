#ifndef CONSUMABLE_H
#define CONSUMABLE_H
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
	void cast_to_concrete_type() noexcept;
	const ConsumableType m_consumableType;
};

#endif