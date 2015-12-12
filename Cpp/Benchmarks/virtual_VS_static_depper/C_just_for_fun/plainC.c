#include <stdio.h>
#include <stdlib.h>
#include "timer.h"
enum ItemType
{
	Weapon,
	Consumable
};

typedef enum WeaponType
{
	Sword,
	Axe
}WeaponType;

typedef enum ConsumableType
{
	HealthPotion,
	ManaPotion
}ConsumableType;

typedef struct Item_t
{
	int m_type;
	const char* m_name;
}Item_t;

typedef struct Weapon_t
{
	struct Item_t base;
	WeaponType m_weaponType;
	int(*attack)(Item_t *const _this);
}Weapon_t;



typedef struct Consumable_t
{
	struct Item_t base;
	ConsumableType m_consumableType;
	int(*consume)(Item_t *const _this);
}Consumable_t;


// the return functions...
int sword_attack(Item_t *const _this) 
{
	return 1;
}
int axe_attack(Item_t *const _this) 
{
	return 2;
}


int health_potion_consume(Item_t *const _this) 
{
	return 1;
}
int mana_potion_consume(Item_t *const _this) 
{
	return 2;
}
// ..


struct Weapon_t * CreateWeapon(const char *name, WeaponType type)
{
	struct Weapon_t *new_weapon = (struct Weapon_t *) malloc(sizeof(struct Weapon_t));
	new_weapon->base.m_name = name;
	new_weapon->base.m_type = Weapon;

	switch (type)
	{
	case Sword:
		new_weapon->m_weaponType = Sword;
		new_weapon->attack = &sword_attack;
		break;
	case Axe:
		new_weapon->m_weaponType = Axe;
		new_weapon->attack = &axe_attack;
		break;
	}

	return new_weapon;
}


struct Consumable_t * CreateConsumable(const char *name, ConsumableType type)
{
	struct Consumable_t *new_consumable = (struct Consumable_t*) malloc(sizeof(struct Consumable_t));
	new_consumable->base.m_name = name;
	new_consumable->base.m_type = Consumable;


	switch (type)
	{
		case HealthPotion:
			new_consumable->m_consumableType = HealthPotion;
			new_consumable->consume = &health_potion_consume;
			break;
		case ManaPotion:
			new_consumable->m_consumableType = ManaPotion;
			new_consumable->consume = &mana_potion_consume;
			break;
	}

	return new_consumable;

}


void DestroyItemVector(Item_t **_vector, int arraySize)
{
	int i;
	for (i = 0; i < arraySize; ++i)
		free(_vector[i]);
}




void use_all_items(Item_t **item_vector, const int itemsInArray)
{
	int swords = 0;
	int axes = 0;
	int healthPotions = 0;
	int manaPotions = 0;


	int i = 0;
	Item_t *ptr;
	ptr = *item_vector;
	for ( ; i < itemsInArray; ++i, ptr = item_vector[i])
	{
		if (ptr->m_type == Weapon) 
		{
			(	((Weapon_t*)ptr)->attack(ptr) == 1	) ? ++swords : ++axes;
		}
		else if (ptr->m_type == Consumable) 
		{
			(	((Consumable_t*)ptr)->consume(ptr) == 1 ) ? ++healthPotions : ++manaPotions;
			
		}
	}


	printf("Swords in list: %i\n", swords);
	printf("Axes in list: %i\n", axes);
	printf("HealthPotions in list: %i\n", healthPotions);
	printf("ManaPotions in list: %i\n", manaPotions);
}





#define MAX_ITEMS 1000000
#define HALF_MAX_ITEMS 500000
#define MAX_LOOP_ITERATIONS = 1000
int main()
{

	
	Item_t **item_vector = (Item_t**) malloc(sizeof(Item_t*) * MAX_ITEMS);
	if (item_vector == NULL)
		return 1;

	Timer timer;
	TIMER_start(&timer);
	int i;


	for (i = 0; i < HALF_MAX_ITEMS; ++i)
	{
		item_vector[i] = (Item_t*)((i % 2 == 0) ? CreateWeapon("Excalibur", Sword) : CreateWeapon("Horned Axe", Axe));
		if (item_vector[i] == NULL)
			return 1;
	}


	for ( ; i < MAX_ITEMS; ++i)
	{
		item_vector[i] = (Item_t*)((i % 2 == 0) ? CreateConsumable("Elixir", HealthPotion) : CreateConsumable("Ether", ManaPotion));
		if (item_vector[i] == NULL)
			return 1;
	}



	

	use_all_items(item_vector, MAX_ITEMS);

	DestroyItemVector(item_vector, MAX_ITEMS);

	double timeElapsed = TIMER_elapsed(&timer);

	printf("Time Elapsed: %f\n", timeElapsed);
	system("pause");
	
}
