#include <iostream>
#include <boost/type_index.hpp>
#define LOG(x) std::cout << x << std::endl
#define PRINT_TYPE(x) LOG(boost::typeindex::type_id_with_cvr<decltype(x)>().pretty_name())


// For exemple only
struct Widget{};

int main() 
{
	// The use of decltype(auto) is not limited to function return types.
	// It can also be convenient for declaring variables where you want to apply the
	// decltype type deduction rules to the initializing expression.

	Widget w;

	const Widget& cw = w;

	auto widg = cw; // auto type deduction, ignore reference, creates a copy of cw 

	decltype(auto) cw2 = cw; // decltype type deduction cw2 is: const Widget& 





}