#include <iostream>

#define LOG(x) std::cout << x << std::endl

struct type_t
{
	type_t() { LOG("default constructor called"); }
	type_t(const type_t& rhs) { LOG("copy constructor called");}
	type_t& operator=(const type_t& type) 
	{
		LOG(" operator= called ");
		return *this;
	}

	
};


type_t foo(const type_t &type)
{
	type_t type2(type);

	return type2;
}


int main()
{
	type_t type = foo(type_t());
	
	type;
	
// im creazy about it
}


