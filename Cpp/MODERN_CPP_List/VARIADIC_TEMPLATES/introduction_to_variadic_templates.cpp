#include <iostream>
#include <string>
#define LOG(x) std::cout << x << std::endl;



/* Variadic Templates

		Before C++11 the only way to write a function that takes an arbitrary number of arguments was to use variadic functions like
		printf, using ellipsis syntax (...), in company of VA_ macros family.
		But there is some problems with that:
			Is type unsafe (all type resolution has to be done explicitly with casts in va_arg, at runtime).
			
			Run-Time: if you intend to use this variadic function only inside your code, sadly you cannot bind things at Compile-Time
					you have to parse arguments and cast at run time...


*/


/* Variadic Templates
		new feature in C++11. Finally a way to write functions that take an arbitrary number of arguments
		in a type sage way and have all the argument handling logic resolved at compile-time.


	Variadic templates can be used for much more than just function that take an arbitrary number of arguments.
	lets see some of these capabilities.
*/



// Basic Example using recursion:
template<typename T>
T adder(T arg) {
	
	return arg;
}

template<typename T, typename ...Args>
T adder(T first, Args... args) {
	/*
	[1] The recursion itself happens in the call adder(args...).Note how the general adder is defined - the first argument
		is peeled off the template parameter pack into type T.So with each call, the parameter pack gets shorter by one parameter.
		eventualy, the base case is encountered.
	*/
	return first + adder(args...);
}


int main() {
	int store = 0;
	store = adder(10, 20, 30, 40);
	LOG(store); // 100

	std::string cat = adder(std::string("bob"), std::string(" shame"), std::string(" kitty"));

	LOG(cat);




	/*	adder will accept any number of arguments, and will compile properly as long it can apply the + operator to them.

	This checking is done by the compiler, at compile time. There's nothing magical about it.
	It follows the C++'s usual template and overload resolution rules

	template<typename... Args> 
		: this is called a template parameter pack
	
	(Args... args)
		: and this is called function parameter pack. (Args is of course, a completely arbitrary name and could be anything else).

	Variadic templates are written just the way you'd write Recursive code:
		
		You need a base case ( adder(T arg) declaration above ), and a general case which "recurses".

	[1] The recursion itself happens in the call adder(args...). Note how the general adder is defined - the first argument
	is peeled off the template parameter pack into type T. So with each call, the parameter pack gets shorter by one parameter.
	eventualy, the base case is encountered.
	
	
	
	*/


}