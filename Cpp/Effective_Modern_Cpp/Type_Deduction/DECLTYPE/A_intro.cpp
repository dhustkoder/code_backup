#include <iostream>
#include <vector>
#include <boost/type_index.hpp>
#define LOG(x) std::cout << x << std::endl

template<typename T>
constexpr void printType() noexcept {
	LOG(boost::typeindex::type_id_with_cvr<T>().pretty_name());
}







int main()
{

	// decltype is an odd creature. Given a name or an expression, decltype
	// tells you the name's or expressions's type

	// Typically, what it tells you is exactly what you'd predict.
	
	// Occasionally however, it provides results that leave you scratching your head.

	// OK, let's begin with typical cases - the ones harboring no surprises.


	// In contrast to what happens during type deduction for templates and auto
	// decltype typically parrots back the exact type of the name or expression
	// you give it:


	const int ci = 0; // decltype int is const int

	printType<decltype(ci)>(); // const int
	
	struct Widget{};
	bool f(const Widget& w); // decltype(w) is const widget&
                             // decltype(f) is bool(const widget&)

	printType<decltype(f)>(); // bool(const main::Widget&)
	
	printType<decltype(f(Widget()))>(); // the result of f(Widget()) expression is bool


	std::vector<int> v ({10,20,30});

	if(v[0] == 10) // v[0] is int&
		printType<decltype(v[0])>();



	// see ? no surprises, perhaps the primary use for decltype is declaring function templates
	// where the function return type depends on the parameters types.

}
