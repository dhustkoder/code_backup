#include <iostream>
#include <vector>
#include <boost/type_index.hpp>
#define LOG(x) std::cout << x << std::endl
#define PRINT_TYPE(x) LOG(boost::typeindex::type_id_with_cvr<decltype(x)>().pretty_name())



// But two things are bothering you, I know. One is the refinement to authAndAccess I
// mentioned, but have not yet described.Let’s address that now.
// Look again at the declaration for the C++14 version of authAndAccess :


template<class Container, class Index>
decltype(auto) authAndAccess_(Container& c, Index i)
{
	// authenticate_user();
	return c[i];
	/*

	The container is passed by lvalue-reference-to-non-const, because returning a refer‐
	ence to an element of the container permits clients to modify that container. But this
	means it’s not possible to pass rvalue containers to this function. Rvalues can’t bind
	to lvalue references (unless they’re lvalue-references-to-const, which is not the case
	here).

	*/
}

std::vector<int> createIntVec()
{
	return { 1, 2, 3 };
}



// So lets do another version, with a universal reference


// C++14 version
template<class Container, class Index>
decltype(auto) authAndAccess(Container&& c, Index i)
{
	//In this template, we don’t know what type of container we’re operating on
	// so we need to make use of std::forward when dealing with container

	// authenticate_user();
	PRINT_TYPE(c);
	return std::forward<Container>(c)[i];
}


// C++11 version
/*
template<class Container, class Index>
auto authAndAccess_Cpp11(Container&& c, Index i) -> decltype(std::forward<Container>(c)[i])
{
	//In this template, we don’t know what type of container we’re operating on
	// so we need to make use of std::forward when dealing with container

	// authenticate_user();
	PRINT_TYPE(c);

	return std::forward<Container>(c)[i];
}
*/
int main()
{
	decltype(auto) ret1 = authAndAccess(createIntVec(), 0);
	// the problem here, is that authAndAccess returns a ref to local variable
	// because createIntVec() is rvalue reference...
	
	LOG(ret1); // undefined behavior, since its a reference to a authAndAccess local variable

	auto intVec = createIntVec();

	decltype(auto) ret2 = authAndAccess(intVec, 0); // ok intVec is lvalue reference

	LOG(ret2); // prints the value in index 0, well defined behavior
	std::cin.ignore();
}