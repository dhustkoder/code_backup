#include <iostream>
#define LOG(x) std::cout << x << std::endl




// Case 1: ParamType is a reference or pointer, but not universal reference

// In that case type deduction works like this:

// 1. if expr's type is a reference , ignore the reference part
// 2. then pattern-match expr's type against ParamType to determine T.


// Consider this:
template<typename T>
void foo(T& param){ // param is a reference
	LOG(std::boolalpha << std::is_const<T>::value);
}

// And we have these variables declarations
int main(){
	int x          = 27;  // int
	const int cx   = x;   // const int
	const int& crx = x;   // const int&

	foo(x);               // T is int, ParamType is int&
	foo(cx);              // T is const int, ParamType is const int&
	foo(crx);             // T is const int, ParamType is const int&
}

