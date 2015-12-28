#include <iostream>
#include <boost/type_index.hpp>
#define LOG(x) std::cout << x << std::endl



template<typename T>
void foo(T param)  // by value
{
	LOG("T's type: " << boost::typeindex::type_id_with_cvr<T>().pretty_name());
	LOG("param's type: " << boost::typeindex::type_id_with_cvr<decltype(param)>().pretty_name());
}
template<typename T>
void foo_2(T* param) // by pointer
{
	LOG("T's type: " << boost::typeindex::type_id_with_cvr<T>().pretty_name());
	LOG("param's type: " << boost::typeindex::type_id_with_cvr<decltype(param)>().pretty_name());

}

int main()
{

	const char* const ptr = "PTR-PTR";

	// ptr is a const pointer to a const char arr

	// ptr is a const pointer so can't be modified (can't point to another location)

	LOG("foo result:");
	foo(ptr);    // now T is const char* and ParamType is const char*
	
	LOG("\nfoo_2 result:");
	foo_2(ptr); // now  T is const char and ParamType is const char*

	// When ptr is passed to foo, the bits in ptr location is copied to param
	// the constness of ptr is ignored but the constness of the data pointed by
	// ptr is keeped.

	// so param's type is const char*, a modifiable pointer to a const character string.

	// and ptr was a const pointer to a const character string.



}
