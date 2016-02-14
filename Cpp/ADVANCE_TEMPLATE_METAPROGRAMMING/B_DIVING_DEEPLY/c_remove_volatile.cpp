#include <iostream>
// Template Meta-Programming C++ 
// Diving in....

// C++11 library metafunction conventions

//1 A metafunction with a type result aliases that result to type:

	// (*) except for a few std:: metafunctions predating this convention
	// e.g iterator_traits has 5 type results; none is named type




// Example of how simple thing can be useful:
template<class T>
struct type_is
{
	using type = T; // this struct will contain the type you just give it
};

// imagine now a remove_(something) metafunction
template<class T>
struct remove_volatile : type_is<T> // will remove volatile
{};


template<class U>// if U is not a volatile
struct remove_volatile<volatile U> : type_is<U> // the same
{};

void remove_volatile_example()
{
	volatile int x = 0;
	
	std::cout << std::boolalpha
	<< std::is_volatile<decltype(x)>::value  // true
	
	<< std::endl
	
	<< std::is_volatile<remove_volatile<decltype(x)>::type>::value // false
	
	<< std::endl;
	

}

int main()
{
	remove_volatile_example();
}