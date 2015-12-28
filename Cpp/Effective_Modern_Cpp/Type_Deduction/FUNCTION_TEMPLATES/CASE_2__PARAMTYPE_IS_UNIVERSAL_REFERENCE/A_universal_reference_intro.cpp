#include <iostream>
#define LOG(x) std::cout << x << std::endl




// ParamType is a universal reference

// Things can be less abvious for templates taking universal reference parameters.

// Such parameters are declared like Rvalue references. (i.e., in a function template taking
// a type parameter T, a universal reference's declared type is T&&), but they behave
// diferently when Lvalue arguments are passed in.


template<typename T>
void foo(T&& param){ // param is a universal reference
	LOG("Is Rvalue ? " << std::boolalpha 
		<< std::is_rvalue_reference<decltype(param)>::value);
	LOG("Is Lvalue ? " << std::boolalpha 
		<< std::is_lvalue_reference<decltype(param)>::value);
}


int main(){
	int x = 27;
	LOG("\t passing x");
	foo(x); // T is int, ParamType is int& ( param is a lvalue reference to an int)


	LOG("\n\n\t passing std::move(x)");
	foo(std::move(x));// T is int, ParamType is int&& ( param is a rvalue reference to an int)

}