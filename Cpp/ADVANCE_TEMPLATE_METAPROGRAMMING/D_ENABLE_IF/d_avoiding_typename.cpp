#include <iostream>
#define LOG(x) std::cout << x << std::endl

// Lets take a loot at enable_if

template<class T>
struct type_is { using type = T; };

template<bool, class T>
struct enable_if : type_is<T> {};

template<class T>
struct enable_if<false,T> {}; // this specialization has no member "type"

// if we declare this:
template<bool condition, class T = void>
using enable_if_t = typename enable_if<condition, T>::type; 


// then we can avoid typename and ::type, and if we want void as return type, no need to specify 
template<class T>
enable_if_t<std::is_integral<T>::value>
foo(T t)
{
	LOG("this is integral of value: " << t);
}


template<class T>
enable_if_t<std::is_floating_point<T>::value>
foo(T t)
{
	LOG("this is floating point of value: " << t);
}

int main(){
	foo(10);
	foo(10.55);
}