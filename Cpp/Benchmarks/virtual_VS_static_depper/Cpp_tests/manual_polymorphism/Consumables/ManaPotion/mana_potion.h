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

int ManaPotion::consume() const noexcept
{
	return 2;
}



void ManaPotion::cast_to_concrete_type() noexcept
{
	this->~ManaPotion();
}

ManaPotion::~ManaPotion()
{
#ifdef DESTRUCTOR_PRINT
	printf("D ManaPotion\n");
#endif
	_asm  mov eax, 0x0;
	m_destructorFree = true;
}


#endif