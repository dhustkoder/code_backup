#include <iostream>
#include <boost/type_index.hpp>
#define LOG(x) std::cout << x << std::endl





// Auto type deduction:
// template type deduction was explained using this concept
template<typename T>
void foo(ParamType param);


int main()
{
	foo(expr); // compilers uses the expr to deduce the type for T and ParamType

	// we can think of T as auto
	// and ParamType as our type specifier for the variable
	
	auto x = 27;         // here the type specifier for x is auto only

	const auto cx = x;   // but here the type specifier is const auto

	const auto& rx = cx; // and here type specifier is const auto&

	// to deduce the types in these examples
	// the compiler act as if there were a template for each declaration
	// as well as a call to that template with the corresponding
	// initialization expression

	template<typename T>
	void func_for_x(T param);        // conceptual template for x

	template<typename T>
	void func_for_cx(const T param); // conceptual template for cx

	template<typename T>
	void func_for_rx(const T& rx);   // conceptual template for rx

	func_for_x(27); // conceptual call to x template

	func_for_cx(x); // conceptual call to cx template

	func_for_rx(cx);// conceptual call to rx template

	
}








