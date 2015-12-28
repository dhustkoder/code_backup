#include <iostream>
#include <boost/type_index.hpp>
#define LOG(x) std::cout << x << std::endl

//... 
// if param were a pointer
template<typename T>
void foo(T* param){ // param is a pointer to T, what is T?
	LOG("T's type: " << boost::typeindex::type_id_with_cvr<T>().pretty_name());
	LOG("param's type: " << boost::typeindex::type_id_with_cvr<decltype(param)>().pretty_name());
}


int main(){
	int x = 27;          // &x is int*
	const int *px = &x;  // px is const int *

	foo(&x);             // T is int, ParamType is int*
	foo(px);             // T is const int, ParamType is const int*

	// By now , you may find yourself yawning and nodding off, because C++s type
	// deduction rules work so naturally for reference and pointer parameters, seeing them
	// in written form is really dull. Everything's just obvious! Which is exactly what you
	// want in a type deduction system.


}
