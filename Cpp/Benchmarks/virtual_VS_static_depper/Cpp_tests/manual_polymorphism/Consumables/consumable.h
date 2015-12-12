#ifndef CONSUMABLE_H
#define CONSUMABLE_H

struct Consumable : Item
{
	enum class ConsumableType
	{
		HealthPotion,
		ManaPotion
	};

	Consumable(const char* name, ConsumableType type);

	int consume() noexcept;
	~Consumable();

private:
	friend class Item;
	void cast_to_concrete_type();
	const ConsumableType m_consumableType;
};

#endif