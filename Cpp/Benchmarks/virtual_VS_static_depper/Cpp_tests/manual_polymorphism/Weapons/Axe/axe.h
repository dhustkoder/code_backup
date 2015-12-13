#ifndef AXE_H
#define AXE_H

struct Axe : Weapon
{
	Axe(const char *name) 
		: Weapon(name, Weapon::WeaponType::Axe)
	{
	}

	int attack() noexcept;

	~Axe();
private:
	friend class Weapon;
	void cast_to_concrete_type() noexcept;
};


int Axe::attack() noexcept
{
	return 2;
}


void Axe::cast_to_concrete_type() noexcept
{
	this->~Axe();
}


Axe::~Axe()
{

	asm volatile( "" : : "g"(this) : );
#ifdef DESTRUCTOR_PRINT
	printf("D Axe\n");
#endif
	m_destructorFree = true;
}





#endif