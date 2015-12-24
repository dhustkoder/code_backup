#include <iostream>
#define LOG(x) std::cout << x << std::endl



int main()
{
	// It's thus easy to understand why braced initialization is called uniform.
	// of C++'s three ways to designate a initializing expression, only braces can be used every where
	

	// A novel feature of braced initialization is that it prohibits implicit narowing conversions among-
	// built-in types

	// that means : If the value in a braced initializer isn't guaranteed to be expressible in by the type
	// of the object being initialized, the code won't compile

	double x, y, z;

	int sum1 { x + y + z }; // Error, sum of doubles may not be expressible as int

	int sum2 ( x + y + z ); // Okay, (value of expression truncated to int )

	int sum3 = x + y + z;   // Okay, same as above	


	// another noteworthy characteristic of braced initialization is its immunity to C++'s
	// most vexing parse. A side effect of C++'s rule that anything that can be parsed as a
	// declarion must be interpreted as one.

	// Imagine that you want to call a object's default constructor

	struct Type
	{
		Type() { LOG("Default constructor"); }
	};


	Type t1(); // most vexing parse declares a function name t1, returns a Type

	Type t2{}; // call default constructor



}
