#include <iostream>
#include <boost/type_index.hpp>
#define LOG(x) std::cout << x << std::endl
#define FWD(x) std::forward<decltype(x)>(x)


template<typename ...Ts>
constexpr void printTypes(Ts&& ...ts) noexcept
{

	(void)std::initializer_list<int>
	{
		0, ( LOG(boost::typeindex::type_id_with_cvr<Ts>().pretty_name()), 0)...
	};

}

void someFunc(int, double){} // someFunc is of type void(int,double)



int main()
{
	// we've seen how array and function types decay into pointer types
	// for no-reference type specifiers, that happens in auto type deduction too:

	const char song[] = "Dancing Mad";
	
	auto arr1 = song;    // song is const char[12] , arr1 is const char *
	
	auto& arr2 = song;   // song is const char[12], arr2 is const char (&) [12]

	auto arr3 = someFunc;    // someFunc is type void(int,double), arr3 is void (*)(int,double)
	
	auto& arr4 = someFunc;   // someFunc is type void(int,double), arr4 is void (&)(int,double)

	printTypes(arr1, arr2, arr3, arr4);

	//as we can see, auto type deduction works like template type deduction

	// they're essentially two sides of the same coin

	// except for one way the differ... 


}







