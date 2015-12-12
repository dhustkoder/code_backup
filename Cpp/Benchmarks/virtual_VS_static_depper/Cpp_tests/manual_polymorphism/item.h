#ifndef ITEM_H
#define ITEM_H
#include <cstdio>


//#define DESTRUCTOR_PRINT

struct Item
{
	enum class ItemType
	{
		Weapon,
		Consumable
	};
	const ItemType m_type;

	Item(const char* name, ItemType type) 
		: m_name(name), m_type(type)
	{
	}

	~Item();
	const char* m_name;
private:
	// this function casts down in hirarchy until the real type of 'this'
	void cast_to_concrete_type() noexcept;
	
protected:
	bool m_destructorFree = false;

};


#endif