#ifndef WEAPON_H
#define WEAPON_H

// interfaces
struct Weapon : Item
{
	enum class WeaponType
	{
		Sword,
		Axe
	};

	Weapon(const char* name, WeaponType type);

	~Weapon();
	int attack() noexcept;
private:
	friend class Item;
	void cast_to_concrete_type() noexcept;
	const WeaponType m_weaponType;
};
#endif