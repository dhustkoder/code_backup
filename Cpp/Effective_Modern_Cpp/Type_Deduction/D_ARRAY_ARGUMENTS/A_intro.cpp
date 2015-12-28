#include <iostream>
#include <boost/type_index.hpp>
#define LOG(x) std::cout << x << std::endl

template<typename T>
constexpr void foo(T param) noexcept{
	LOG("T's type:" << boost::typeindex::type_id_with_cvr<T>().pretty_name());
	LOG("ParamType: " << boost::typeindex::type_id_with_cvr<decltype(param)>().pretty_name());
}


int main()
{
	// There is something else that I needed to learn. It's that array types are 
	// different from pointer types. Even though they sometimes seem to be interchangeable.
	// A primary contributor to this illusion is that, in many contexts, an array decays into
	// a pointer to its first element.

	// this decay is what permits code like this to compile:
	const char arr[] = "Briggs and Wedge";
	const char* ptrToArr = arr;
	
	// Here the const char* pointer ptrToArr is being initialized with arr, which is a 
	// const char[16]. These types (const char* and const char[13]) are not the same

	// But because of the array-to-pointer decay rule, the code compiles.
	// but what if an array is passed to a templed taking by-value parameter?
	foo(arr); // what types are deduced for T and param ?

	// we begin with the observation that there is no such thing as a function parameter
	// that's an array. Yes , the syntax is legal,
	void someFunc(int param[]);

	// But the array declaration is treated as a pointer declaration, meaning that 
	// 'someFunc' could equivalently be declared like this:
	void someFunc(int *param); // same as above


	// This equivalency  of array and pointer is a bit of foliage springing from the 
	// C roots at the base of C++, and it fosters the illusion that array and pointer types are
	// the same

	// Because array parameter declarations are treated as if they were poitner parameters,
	// the type of an array that's passed to a template function by value is deduced to be a
	// pointer type. that means that in the call to the template foo, its type parameter
	// T is deduced to be const char*

	foo(arr); // arr is array. but T is deduced as const char*

}