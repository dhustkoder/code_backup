#include "item.h"
#include "Consumables/consumable.h"
#include "Weapons/weapon.h"

// Base classes Destructors
void Item::cast_to_concrete_type() noexcept
{
	switch (m_type)
	{
		case ItemType::Weapon:
			static_cast<Weapon*>(this)->cast_to_concrete_type();
			return;
		case ItemType::Consumable:
			static_cast<Consumable*>(this)->cast_to_concrete_type();
			return;
	}

}


Item::~Item()
{
	if (m_destructorFree)
	{
#ifdef DESTRUCTOR_PRINT
		printf("D Item\n");
#endif
		_asm  mov eax, 0x0;  // fake destruction operations.
	}
	else
		this->cast_to_concrete_type();

}
