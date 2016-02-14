#include <iostream>
#include <boost/type_index.hpp>
#define DCT(x) decltype(x)
#define LOG(x) std::cout << x << std::endl



template<typename ...Ts>
constexpr void printTypes() noexcept
{
	return (void)std::initializer_list<int>
	{	
		0, (LOG(boost::typeindex::type_id_with_cvr<Ts>().pretty_name()), 0)...
	};

}

template<typename T>
void foo(T param) {

}
template<typename T>
void foo2(std::initializer_list<T> param) {

}

int main()
{
	// so auto and templates are almost the same except for some situations 

	// lets begin observing the initialization syntax C++98 gives us to initialize some variable
	{
		int x1 = 27;
		int x2(27);

		// C++11 support uniform initialization. adds these:

		int x3 = { 27 };

		int x4 { 27 };
	}
	// all 4 syntaxes have the same result, int with value 27

        // ok, what happen if we replace int for auto ?


	auto x1 = 27; // x1 is int
	auto x2 (27); // x2 is int

	auto x3 = { 27 }; // x3 is initializer_list<int>
	auto x4 { 27 };   // C++14 x4 is initializer_list<int>, C++17 x4 is int


	printTypes<DCT(x1), DCT(x2), DCT(x3), DCT(x4)>();

	// these declarations all compile, but they don't have the same meaning as the ones they replace.
	// the first 2 statements will, indeed, declare a variable of type int, with value 27
	// the second 2 statements will declare a initializer_list<int>
	// in C++17 the x4 would be a int

	// C++17
	auto var1 = { 27 }; // initializer_list<int>
	auto var2{ 27 };    // int

	// This happens because of a special type deduction rule for auto.
	// : When the initializer for a auto-declared variable is enclosed in braces,
	// the deduced type is initializer_list. If such type can't be deduced the code
	// will be rejected:

	auto var3 = { 10, 20, 3.0 }; // error
	// that happens because is 2 type deduction happening
	// one for auto that happens to be initializer_list<T>

	// and then the type of T in initializer_list<T> that must be 1 type

	// that's the way template and auto differ, because if you try yo call
	// a template function with braced initializer trying to get
	// the template deduce the type for T as initializer_list the code will fail


	foo({ 10,20,30 }); // can't deduce type for T...
	auto var4 = { 10,20,30 }; // var4 is initializer_list<int>

	// but if you try with ParamType as std::initializer_list<T>
	// template<typename T> void foo2(std::initializer_list<T> param) {}

	// then it works
	foo2({ 10,20,30 }); // works, T is int, ParamType is std::initializer_list<int>


}
