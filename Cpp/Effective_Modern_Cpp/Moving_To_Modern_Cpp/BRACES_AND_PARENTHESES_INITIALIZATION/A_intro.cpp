#include <iostream>
#define LOG(x) std::cout << x << std::endl







int main()
{
	// Ditinguish between () and {} when creating objects


	int x(0);     // initializer is in parentheses

	int y = 0;    // initializer follows "="

	int z {0};    // initializer is in braces

	int z2 = {0}; // initializer uses "=" and braces (usually the same as above)


	// the confusing mess lobby points out that the use of an equals sign
	// for iniialization can misleads C++ newbies that an assignment is taking place but its not.
	// for primitive - built-in types the difference is academic, but for user defined types its
	// important to distinguish initialization from assigment because diferent functions calls are involved:

	struct Widget
	{
		// default constructor
		Widget(){
		LOG("default ctor called!");
		}                 

		// copy constructor
		Widget(const Widget&){
			LOG("copy ctor called!");
		} 

		// assigment operator       
		Widget& operator=(const Widget&){
			LOG("assigment operator called!");
			return *this;
		} 
	};


	Widget w;        // call default ctor
	Widget w2 = w;   // call copy ctor
	w = w2;          // call assigment operaor




}