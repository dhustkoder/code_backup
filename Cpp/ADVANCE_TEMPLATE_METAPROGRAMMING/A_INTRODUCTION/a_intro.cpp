#include <iostream>


// First of all. What is Metaprogramming ?

//	 is the writting of computers programs that :
	
//		1 -  That write or manipulate other programs ( or themselves ) as their data

//		2 - That do work at compile time that otherwise could happen to be done at run-time



// C++ Template Metaprogramming uses template instantiation to drive compile-time evaluation


// NOTE: When we use the name of a template where a (function, or type, or variable) is expected, 
// What happens is: The compiler will INSTANTIATE (create) the expected entity from that template

// Example
template<class T> void f(T x)
{
	x.saySomething();

}

void example_1()
{
	struct some_type { void saySomething(){ std::cout << "Hello, I'm some_type" << std::endl;}};
	some_type x;
	f(x);
	
	// The compiler generates a function
	// exactly like f, but instead of T as parameter it is now some_type
	
	struct another_type {void saySomething(){std::cout << "hey there!, I'm another type" << std::endl;}};
	another_type y;
	f(y);

	// now The compiler again generates another function
	// instead of T or some_type, it's parameter now is " another_type "
	
}


// Template Metaprogramming exploit this machinery to 2 main reasons.
// 1. Improve source code flexibility. ( now we don't have to write 2 functions one for some_type and other for another_type)
// 2. Improve Run-Time performance. ( by doing operations at compile-time )


// This is not free. 
// Compile time can increase... you have to decide what values most to you. but compile-time have done great improvements


int main()
{
	example_1();
}