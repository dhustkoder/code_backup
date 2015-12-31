#include <iostream>
#include <vector>
#include <boost/type_index.hpp>
#define LOG(x) std::cout << x << std::endl

// using decltype do define a function template that the return type
// depends on the type of template parameter

// supose we'd like to write a function that takes a container that support indexing via square brackets ("[]")
// plus a index, then authenticates the user before returning the result of the indexing operation.

// the return type of the function should be the same as the type returned by the indexing operation ( [] )

// operator [] of a container typically returns T& . That is the case of std::deque, for example, and it's almost the case
// for std::vector. For std::vector<bool>, however , operator[] return a brand new object, is T operator[]

// but what is important here is that the type returned by a container's operator[] depends on the container


template<typename T>
void printType() noexcept{
	LOG(boost::typeindex::type_id_with_cvr<T>().pretty_name());
}



// C++14 style with direclty auto deduced return type
template<typename Container, typename Index>
auto foo_1(Container& c, const Index i)   // can't do foo_1(...) = some_value; because foo_1 returns by value ( constness of expression c[i] is ignored )
{
	// authenticate_user();
	return c[i];
}

// C++11 auto return type with trailing return type
template<typename Container, typename Index>
auto foo_2(Container& c, const Index i) -> decltype(c[i]) // works, the return type will be exactly what operator[] returns
{							  // decltype doesn't ignore constness
	// authenticate_user();
	return c[i];

}

int main()
{

	std::vector<int> v {10,20,30};	

	// as you see if we want to modify a value we do
	v[0] = 15;

	// ok but if we want to modify , the index returned by foo_1

	//foo_1(v, 0) = 10; // error;

	// because foo_1 returns int, not int&
	printType<decltype(foo_1(v,0))>();

	LOG(foo_1(v,0)); // prints 15

	// so foo_2 uses decltype to return exactly what expression v[0] returns
	foo_2(v,0) = 8;
	LOG(foo_2(v,0));


	// and as I said std::vector<bool> does not return by reference
	std::vector<bool> vBool{true,false};

	printType<decltype(vBool[0])>();
	
	LOG(vBool[0]);
	vBool[0] = false;
	LOG(vBool[0]);

	// turns out that in C++11 and C++14 there is std::_Bit_reference
	// and vector<bool> returns a reference to a bit
}
