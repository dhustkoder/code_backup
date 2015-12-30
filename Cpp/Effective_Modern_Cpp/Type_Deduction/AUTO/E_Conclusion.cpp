#include <iostream>
#include <vector>
#define LOG(x) std::cout << x << std::endl



// for C++11 this is the full story, but for C++14, the tale continues. C++14
// permits auto to indicate that a function return type should be deduced.
// and C++14 lamdas may use auto in parameter declarations. However these uses
// of AUTO employ template type deduction, not AUTO type deduction, so functions
// which returns a braced initializer wont compile

// like this

auto createInitList(){
	return {1,2,3};    // error, can't deduce type for {1,2,3}
}

// but compile like this:
template<typename T>
std::initializer_list<T> createInitList(){
	return {1,2,3};
}


int main(){
	// the same is true when a auto is declared in a C++14 lambda
	std::vector<int> v;
	
	auto lamb = [&v](const auto& param){
		v = param;
	};

	lamb({10,20,30}); // error, can't deduce type for 10,20,30

	
	auto lamb2 = [&v](const std::initializer_list<auto>& param){
		v = param;
	};

	lamb2({10,20,30}); // ok


	// Things to remember
	
	// *auto type deduction is usually the same as template type deduction,
	// but auto type deduction assumes that a braced initializer reprents a std::initializer_list
	// and template type deduction doesn't

	// *auto in a function return type or lambda parameter implies template type deduction, not auto type deduction


}