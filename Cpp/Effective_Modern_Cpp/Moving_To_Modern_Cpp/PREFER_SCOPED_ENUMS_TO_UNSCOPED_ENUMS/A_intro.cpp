#include <iostream>
#include <boost/type_index.hpp>
#define LOG(x) std::cout << x << std::endl
#define TYPESTR(x) boost::typeindex::type_id_with_cvr<decltype(x)>().pretty_name()


// PREFER SCOPED ENUMS TO UNSCOPED ENUMS

// as a general rule, declaring a name inside a curly braces limits the visibility of
// that name to the scope defined by braces. Not so for enumerators declared in C++98-style enums
// The names of such enumerators belongs to the scope containing the enum.
// And that means that nothing else in that scope may have the same name :

void example1()
{
	enum Color { black, white, red };
	auto white = false; // error
}

// The fact that these enumerators names leak into the scope containg their enum definition
// gives rise to the official term for this kind of enum: unscoped.
// Their new C++11 counterparts, scoped enums, don't leak names in this way:

void example2()
{
	enum class Color { black, white, red};
	auto white = false; // fine

	//Color color = white; // error, no enumarator named white,

	Color color = Color::white; // fine
	auto color2 = Color::black; // fine
}

// Because scoped enums are declared via "enum class", they're sometimes referred to as enum classes


// The reduction in namespace pollution offered by scoped enums is reason enough
// to prefer them over thei unscoped siblings, but scoped enums have a second compelling advantage:
// their enumerators are much more strongly typed.

// Enumerators for unscoped enums implicity convert to integral types (and, from there , to floating-point types)
// Semantic travesties such as the following are therefore completely valid

#include <vector>
void example3()
{
	enum Color {black, white, red};
	auto primeFactors = [](std::size_t x) // function returning prime factors of x
	{
		std::vector<std::size_t> vec;
		// compute prime factors ...
		return std::move(vec);
	};

	Color c = red;
	// ...
	if (c < 14.5) {
		auto factors = primeFactors(c);
		// ....
	}
	
}

// Thow a simple "class" after "enum", however, thus transforming an unscoped
// enum intro a scoped one, and it's a very different story , there are no implicit convrsions
// from enumerators in a scoped enum to any other type


void example4()
{
	enum class Color {black, white, red};

	auto primeFactors = [](std::size_t x) // function returning prime factors of x
	{
		std::vector<std::size_t> vec;
		// compute prime factors ...
		return std::move(vec);
	};

	Color c = Color::red; // as before but with scope qualifier

	if (c < 14.5) { // error, cant compare color and floating-point-type
		auto factors = primeFactors(c); // error can't pass color to function expecting std::size_t
	}
}

// If you honestly want to perform a conversion from Color to a different type, do
// what you always do twist the type system to wanted desires -- use a cast:
void example5()
{
	enum class Color { black, white, red };
	auto primeFactors = [](std::size_t x) // function returning prime factors of x
	{
		std::vector<std::size_t> vec;
		// compute prime factors ...
		return std::move(vec);
	};

	Color c = Color::red;
	// ...
	if (static_cast<double>(c) < 14.5) { /// odd code, but it's valid
		auto factors = primeFactors(static_cast<std::size_t>(c)); // suspect, but compiles
		// ....
	}

}



int main()
{



}