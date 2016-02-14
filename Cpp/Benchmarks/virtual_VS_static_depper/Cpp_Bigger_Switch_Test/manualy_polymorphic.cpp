#include <iostream>
#include <vector>
#include <exception>
#include "timer.h"

class Item
{
public:
	enum ItemType
	{
		A, B, C, D, E, F, G, H, I, DESTROYED
	};
	Item(ItemType type) : m_type(type){}
	~Item();
	int use();
	ItemType m_type;


};

template<int n>
class XPotion : public Item
{
public:
	XPotion() : Item(static_cast<ItemType>(n))
	{}
	int use(){
		return n;
	}
	
	~XPotion(){
		//printf("Destroyed XPotion<%i>!\n", n);
		this->m_type = ItemType::DESTROYED;
	}
};

int Item::use()
{
	switch(m_type)
	{
		case A:
			return static_cast<XPotion<A>*>(this)->use();
		case B:						     
			return static_cast<XPotion<B>*>(this)->use();
		case C:						     
			return static_cast<XPotion<C>*>(this)->use();
		case D:						     
			return static_cast<XPotion<D>*>(this)->use();
		case E:						     
			return static_cast<XPotion<E>*>(this)->use();
		case F:						     
			return static_cast<XPotion<F>*>(this)->use();
		case G:						     
			return static_cast<XPotion<G>*>(this)->use();
		case H:						     
			return static_cast<XPotion<H>*>(this)->use();
		case I:						     
			return static_cast<XPotion<I>*>(this)->use();
		default:
			break;
			
	}

	
}

Item::~Item()
{
	if(m_type != ItemType::DESTROYED)
	{
		switch(m_type)
		{
			case A:
				static_cast<XPotion<A>*>(this)->~XPotion();
				break;
			case B:						  
				static_cast<XPotion<B>*>(this)->~XPotion();
				break;
			case C:						   
				static_cast<XPotion<C>*>(this)->~XPotion();
				break;
			case D:						  
				static_cast<XPotion<D>*>(this)->~XPotion();
				break;
			case E:						  
				static_cast<XPotion<E>*>(this)->~XPotion();
				break;
			case F:						 
				static_cast<XPotion<F>*>(this)->~XPotion();
				break;
			case G:						 
				static_cast<XPotion<G>*>(this)->~XPotion();
				break;
			case H:						 
				static_cast<XPotion<H>*>(this)->~XPotion();
				break;
			case I:						 
				static_cast<XPotion<I>*>(this)->~XPotion();
				break;
			default:
				break;
				
		}
		
	}
	//else
		//printf("Item destroyed\n");
}






void use_all_items(std::vector<Item*> &vec)
{
	unsigned objectCount[9]{0};

	for(auto item : vec)
	{
	
		++objectCount[item->use()];
	
	}
	
	for(int i{0}; i < 9; ++i)
		printf("Potion<%i> :: count: %u\n", i,objectCount[i]);

}



constexpr int MAX_ITEMS = 999999;

int main()
{
	std::vector<Item*> vec;
	vec.reserve(MAX_ITEMS);
	
	
	for(int i =0, j = 0 ; i < MAX_ITEMS; ++i, ++j)
	{
		switch(j)
		{
			case 0:
				vec.push_back(new XPotion<0>());
				continue;
			case 1:
				vec.push_back(new XPotion<1>());
				continue;
			case 2:
				vec.push_back(new XPotion<2>());
				continue;
			case 3:
				vec.push_back(new XPotion<3>());
				continue;
			case 4:
				vec.push_back(new XPotion<4>());
				continue;
			case 5:
				vec.push_back(new XPotion<5>());
				continue;
			case 6:
				vec.push_back(new XPotion<6>());
				continue;
			case 7:
				vec.push_back(new XPotion<7>());
				continue;
			case 8:
				vec.push_back(new XPotion<8>());
				continue;
			default:
				j = -1;
				continue;
			
			
			
		}	
	}
	
	
	
	Timer timer;
	timer.start();
	use_all_items(vec);
	use_all_items(vec);
	use_all_items(vec);
	use_all_items(vec);
	use_all_items(vec);
	
	printf("\n\n\t TIME ELAPSED: %f\n\n", timer.elapsed());

	for(int i = 0; i < vec.size(); ++i)
		delete vec[i];
}