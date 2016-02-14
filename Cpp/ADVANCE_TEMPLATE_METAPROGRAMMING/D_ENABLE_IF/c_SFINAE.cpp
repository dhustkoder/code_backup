#include <iostream>
#define LOG(x) std::cout << x << std::endl

// Lets take a loot at enable_if

template<class T>
struct type_is { using type = T; };

template<bool, class T>
struct enable_if : type_is<T> {};

template<class T>
struct enable_if<false,T> {}; // this specialization has no member "type"


template<class T>
typename enable_if<std::is_integral<T>::value, void>::type 
foo(T t)
{
	LOG("this is integral of value: " << t);
}


template<class T>
typename enable_if<std::is_floating_point<T>::value, void>::type 
foo(T t)
{
	LOG("this is floating point of value: " << t);
}


int main(){

	foo(10.23); // so the first foo() will not have the member "type", so the compiler should give us an error ...

	// well it will not give an error in this case. because we have another case: std::is_floating_point. that matches.

	// this is called SFINAE:

	// Substitution Failure Is Not An Error

	// Formally known as Explicit Overload Set Management



	// SFINAE Happens during template instantiation:

	// during template instantiation, the compiler will:

	// Obtain (or figure out) the template argumets

	// Taken verbatim if explicit supplied at template's point of use

	// Else deduced from function arguments at point of cal


	// Else taken from the declaration's default template argument






}