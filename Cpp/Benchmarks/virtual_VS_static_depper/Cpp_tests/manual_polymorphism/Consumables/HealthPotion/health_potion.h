#ifndef HEALTH_POTION_H
#define HEALTH_POTION_H

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



int HealthPotion::consume() const noexcept
{
	return 1;
}


void HealthPotion::cast_to_concrete_type() noexcept
{
	this->~HealthPotion();
}

HealthPotion::~HealthPotion()
{
#ifdef DESTRUCTOR_PRINT
	printf("D HealthPotion\n");
#endif
	_asm  mov eax, 0x0;
	m_destructorFree = true;
}

#endif