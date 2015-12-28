#include <iostream>
#include <boost/type_index.hpp>
#define LOG(x) std::cout << x << std::endl

// But now comes a curve ball. Although functions can't declare parameters
// that are truly arrays, they can declare parameters that are references to arrays!
// The type includes the size of the array, so in this example, T is deduced to be const char[13],
// and the type of foo's parameter 'param' (a reference to this array) is const char (&) [13].
template<typename T>
void foo(T& param){
	LOG("T's type: " << boost::typeindex::type_id_with_cvr<T>().pretty_name());
	LOG("ParamType: " << boost::typeindex::type_id_with_cvr<decltype(param)>().pretty_name());
}


// Interestingly, the ability to declare references to arrays enables creation of a template
// that deduces the number of elements that an array constains
template<typename T, std::size_t N>
constexpr std::size_t arraySize(T(&)[N]) noexcept{
	return N;
}

int main()
{
	const char paladin[] = "Cecil Harvey"; // paladin is char[13]
	const char (&arrRef)[13] = paladin;		// arrRef is a reference to const char[13]

	foo(paladin); // T is const char [13], ParamType is const char (&) [13]
	foo(arrRef);  // T is const char [13], ParamType is const char (&) [13]
	LOG(arraySize(paladin)); // returns array size


}