#include <iostream>
#include <boost/type_index.hpp>
#define LOG(x) std::cout << x << std::endl
#define PRINT_TYPE(x) LOG(boost::typeindex::type_id_with_cvr<decltype(x)>().pretty_name())



int main()
{
	// Truth be told, you're unlikely to encounter these exceptions to the rule unless
	// you're a heavy-duty library implementer
	


}