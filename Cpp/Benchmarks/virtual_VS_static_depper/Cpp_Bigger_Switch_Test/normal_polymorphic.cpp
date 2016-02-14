#include <iostream>
#include <vector>
#include "timer.h"

char getTypeChar(int x)
{
	switch(x)
	{
		case 0: return 'A';
		case 1: return 'B';
		case 2: return 'C';
		case 3: return 'D';
		case 4: return 'E';
		case 5: return 'F';
		case 6: return 'G';
		case 7: return 'H';
		case 8: return 'I';
		default: return 'X';
		
	}
}

class Item // interface
{
public:
	virtual int use() = 0;


};

struct APotion : Item
{

	int use()
	{
		return 0;
	}
};


struct BPotion : Item
{

	int use()
	{
		return 1;
	}
};


struct CPotion : Item
{
	
	int use()
	{
		return 2;
	}
};


struct DPotion : Item
{
	
	int use()
	{
		return 3;
	}
};


struct EPotion : Item
{
	
	int use()
	{
		return 4;
	}
};


struct FPotion : Item
{
	
	int use()
	{
		return 5;
	}
};


struct GPotion : Item
{
	
	int use()
	{
		return 6;
	}
};


struct HPotion : Item
{
	
	int use()
	{
		return 7;
	}
};


struct IPotion : Item
{
	
	int use()
	{
		return 8;
	}
};



void use_all_items(std::vector<Item*> &vec)
{
	unsigned objectCount[9]{0};

	for(auto item : vec)
	{
	
		++objectCount[item->use()];
	
	}
	
	for(int i{0}; i < 9; ++i)
		printf("%c :: count: %u\n",getTypeChar(i),objectCount[i]);

}



constexpr unsigned MAX_ITEMS = 999999;
int main()
{
	std::vector<Item*> vec;
	vec.reserve(MAX_ITEMS);
	
	
	for(int i =0, j = 0 ; i < MAX_ITEMS; ++i, ++j)
	{
		switch(j)
		{
			case 0:
				vec.push_back(new APotion());
				continue;
			case 1:
				vec.push_back(new BPotion());
				continue;
			case 2:
				vec.push_back(new CPotion());
				continue;
			case 3:
				vec.push_back(new DPotion());
				continue;
			case 4:
				vec.push_back(new EPotion());
				continue;
			case 5:
				vec.push_back(new FPotion());
				continue;
			case 6:
				vec.push_back(new GPotion());
				continue;
			case 7:
				vec.push_back(new HPotion());
				continue;
			case 8:
				vec.push_back(new IPotion());
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
	
	
}