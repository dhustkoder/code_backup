#include <iostream>
#include <boost/type_index.hpp>
#define LOG(x) std::cout << x << std::endl



// Type Deduction:
// FUNCTION ARGUMENTS...

// Arrays aren't the only thing that can decay to pointers in C++,
// function types can decay into function pointers. 

// And everything we covered about type deduction for array types
// applies to type deduction for function types and their decay
// into function pointers.


void someFunc(int, double){
	LOG("hello I'm in someFunc");
}
// someFunc is of type void(int,double)


template<typename T>
void foo(T param) // foo: param is passed by value
{
	LOG("T's type: " << boost::typeindex::type_id_with_cvr<T>().pretty_name());
	LOG("param's type: " << boost::typeindex::type_id_with_cvr<decltype(param)>().pretty_name());
}

template<typename T>
void foo2(T& param) // foo2: param is passed by reference
{
	LOG("T's type: " << boost::typeindex::type_id_with_cvr<T>().pretty_name());
	LOG("param's type: " << boost::typeindex::type_id_with_cvr<decltype(param)>().pretty_name());
}



int main()
{
	foo(someFunc); // T is void (*) (int,double), param is void (*) (int,double)
	// so in foo, the function was passed by pointer, the pointer was passed by value

	foo2(someFunc); // T is void(int,double), param is void(&)(int,double)

	

}




