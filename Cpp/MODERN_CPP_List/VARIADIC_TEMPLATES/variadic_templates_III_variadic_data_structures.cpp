#include <iostream>
#include <string>
#define LOG(x)	std::cout << x << std::endl

/* Variadic data structures 

	This can be more interesting,  because it was something that just wasn't possible prior to
	introduction of C++11, at least without considerable hackery


	Custom data structures (structs since the times of C and classes in C++) have compile-time defined fields.
	They can represent types that grow at runtime

*/

struct Test
{

	struct iter {
		int x = 10;
	};
	
};
template<class T>
void test(T t) {
	typename T::iter *itr;
	itr = new T::iter();
	LOG(itr->x);
}


template<typename ...Args>
void foo(Args ...args) {
	[](...) {}((std::cout << args << std::endl)...);
}



int main() {

	test((Test()));
}