#include <iostream>
#define LOG(x) std::cout << x << std::endl

int main()
{
	
	// one more case to std::initializer_list as parameter to constructo

	// what if you call the constructor with empty braced initializer '{}' ?

	struct Widget
	{
		Widget() { LOG("Default constructor"); }
		Widget(std::initializer_list<int> il) { LOG("initializer_list constructor"); }
	
	};


	Widget w1;   // calls default constructor
	Widget w2{}; // also calls default constructor this time.

	// happens that an empty braced initializer  means no arguments, not empty initializer list...


	Widget w3({}); // calls initializer_list constructor with empty initializer_list
	Widget w4{{}}; // same as above

	Widget w5();   // declares a function




}
