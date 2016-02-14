#include <iostream>
// Template Meta-Programming C++ 
// Diving in....


// A metafunction can also produce a type as its result


// Example: "remove" a type's const-qualification:
	// no real removal; "give me the equivalent type without const."
	


// primary template handles types that are not const-qualified
template<class T>
struct remove_const
{
	using type = T;
};

// partial specialization recognizes const qualified types:
template<class U>
struct remove_const<const U> // <= receive const U
{
	using type = U; // return  U
};

int main()
{
	typedef const int _CON_INT;
	
	
	_CON_INT x = 20;
	
	// x = 40; error
	
	remove_const<_CON_INT>::type _x = 20;
	
	_x = 30; // ok
	
	
	

}