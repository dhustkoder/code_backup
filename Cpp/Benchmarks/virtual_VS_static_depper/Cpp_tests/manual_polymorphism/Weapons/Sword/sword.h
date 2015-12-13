#ifndef SWORD_H
#define SWORD_H

// concrete
struct Sword : Weapon
{
	Sword(const char *name) 
		: Weapon(name, Weapon::WeaponType::Sword)
	{
	}

	int attack() noexcept;
	~Sword();
private:
	friend class Weapon;
	void cast_to_concrete_type() noexcept;
};


inline int Sword::attack() noexcept
{
	return 1;
}


inline void Sword::cast_to_concrete_type() noexcept
{
	this->~Sword();
}


Sword::~Sword()
{
	asm volatile( "" : : "g"(this) : );
#ifdef DESTRUCTOR_PRINT
	printf("D Sword\n");
#endif
	m_destructorFree = true;
}





#endif