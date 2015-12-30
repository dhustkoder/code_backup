#include <iostream>
#include <boost/type_index.hpp>
#define DCT(x) decltype(x)
#define LOG(x) std::cout << x << std::endl



template<typename ...Ts>
constexpr void printTypes() noexcept
{
	return (void)std::initializer_list<int>
	{	
		0, (LOG(boost::typeindex::type_id_with_cvr<Ts>().pretty_name()), 0)...
	};

}

int main()
{
	// so auto and templates are almost the same except for some situations 

	// lets begin observing the initialization syntax C++98 gives us to initialize some variable
	{
		int x1 = 27;
		int x2(27);

		// C++11 support uniform initialization. adds these:

		int x3 = { 27 };

		int x4 { 27 };
	}
	// all 4 syntaxes have the same result, int with value 27

        // ok, what happen if we replace int for auto ?


	auto x1 = 27; // x1 is int
	auto x2 (27); // x2 is int

	auto x3 = { 27 }; // x3 is initializer_list<int>
	auto x4 { 27 };   // C++14 x4 is initializer_list<int>, C++17 x4 is int


	printTypes<DCT(x1), DCT(x2), DCT(x3), DCT(x4)>();

	// these declarations all compile, but they don't have the same meaning as the ones they replace.
	// the first    	


}
