#include <iostream>
#include <boost/type_index.hpp>
#define LOG(x) std::cout << x << std::endl
#define FWD(x) std::forward<decltype(x)>(x)


template<typename ...Ts>
void printTypes(Ts&& ...args)
{

	(void)std::initializer_list<int>
	{
		0, ( LOG(boost::typeindex::type_id_with_cvr<decltype(args)>().pretty_name()), 0)...
	};

}

int main()
{

	// as for template type deduction, auto have 3 cases as well
	// based on characteristics of ParamType, the type specifier of general function template
	
	// a variable declaration using auto, the type specifier takes place of ParamType,
	// so there are three cases too:


	// 1 - The type specifier is a pointer or a reference but not universal reference
	// 2 - The type specifier is a universal reference.
	// 3 - The type specifier is neither a reference nor a pointer.


	auto x = 27;         // case 3 , type specifier isn't a reference nor pointer
	const auto cx = x;   // case 3 too.

	const auto& rx = cx; // case 1, type specifier is a reference


	// for universal references we already know the rules

	auto&& uref1 = x;   // x is lvalue so uref1 type is int&
	auto&& uref2 = cx;  // cx is const lvalue, so uref2 is const int&
	auto&& uref3 = rx;  // rx is const lvalue ref, so uref3 is const int& (same as above)

	auto&& uref4 = 27;  // 27 is rvalue so uref4 is, int&&

	printTypes(FWD(uref1), FWD(uref2), FWD(uref3), FWD(uref4));

}
