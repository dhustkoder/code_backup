#ifndef HEALTH_POTION_H
#define HEALTH_POTION_H
#include "../consumable.h"
struct HealthPotion : Consumable
{
	HealthPotion(const char* name) 
		: Consumable(name, ConsumableType::HealthPotion)
	{
	}

	int consume() const noexcept;
	~HealthPotion();
private:
	friend class Consumable;
	void cast_to_concrete_type() noexcept;

};



inline int HealthPotion::consume() const noexcept
{
	return 1;
}


inline void HealthPotion::cast_to_concrete_type() noexcept
{
	this->~HealthPotion();
}

inline HealthPotion::~HealthPotion()
{
#ifdef DESTRUCTOR_PRINT
	printf("D HealthPotion\n");
#endif
	asm volatile( "" : : "g"(this) : );
	m_destructorFree = true;
}

#endif