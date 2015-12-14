#ifndef MANA_POTION_H
#define MANA_POTION_H

struct ManaPotion : Consumable
{
	ManaPotion(const char* name) 
		: Consumable(name, ConsumableType::ManaPotion)
	{
	}

	int consume() const noexcept;
	~ManaPotion();
private:
	friend class Consumable;
	void cast_to_concrete_type() noexcept;
};

inline int ManaPotion::consume() const noexcept
{
	return 2;
}



inline void ManaPotion::cast_to_concrete_type() noexcept
{
	this->~ManaPotion();
}

inline ManaPotion::~ManaPotion()
{
#ifdef DESTRUCTOR_PRINT
	printf("D ManaPotion\n");
#endif
	asm volatile( "" : : "g"(this) : );
	m_destructorFree = true;
}


#endif