#include <iostream>
#include <vector>
#include <algorithm>
#include <boost/type_index.hpp>


void example_1()
{


	// all that changed in C++11, now const_iterators
	// are both easy to get and easy to use.

	// the Container member functions cbegin() and cend()
	// produce const_iterators
	// even for non-const containers
	// and STL member functions that use iterators
	// to identify positions (e.g, insert and erase)
	// actually use const_iterators. Revising the original
	// C++98 code that uses iterators to use const_iterators
	// in C++11 is truly trivial


	
	std::vector<int> vec = {1500, 1293, 1983, 2004, 2001, 19999};

	auto itr = std::find(vec.cbegin(), vec.cend(), 1983); // uses const_iterators
	vec.insert(itr, 1998); // insert


	std::cout << boost::typeindex::type_id_with_cvr<decltype(itr)>().pretty_name() << std::endl;
	std::cout << vec[2] << std::endl;



}

// Now thats code using const_iterators that's pratical!


	// About the only situation in which C++11's support for const_iterators 
	// comes up bit short is when you want to write maximally generic library code.
	// Such code takes into account that some containers and container-like data
	// structures offer begin and end (plus cbegin, cend, rbegin, erc) as non-member functions.

	// This is the case for built-in arrays, for example, and it's also the case 
	// for some third-party libraries with interfaces consisting only of free functions.
	// Maximally generic code thus uses non-member functions rather than assuming the existence of
	// members versions


	// For example, we could generalize the code we've been working with into a findAndInsert template as follows

template<class C, class V>
void findAndInsert(C& container, const V& targetVal, const V& insertVal)
{
	using std::cbegin;
	using std::cend;
	auto itr = std::find(cbegin(container), cend(container), targetVal);
	container.insert(itr, insertVal);
}


void example_2()
{
	std::vector<int> vec { 10, 20, 30 };
	findAndInsert(vec, 20, 50);
	std::cout << vec[1] << std::endl;

}
// This works fine in C++14, but sadly, not in C++11.
// Through an oversight during standarlization, C++11
// added the non-member functions begin and end,
// but failed to add cbegin, cend, rbegin, rend, crbegin, crend.
// C++14 rectifies that oversight


// If you're using C++11, you want to write maximally generic code, and none of
// the libraries you're using provides the missing templates for non-member cbegin
// and friends, you can throw your own implementations together with ease.
// for example here's an implementation of non-member cbegin
template<class C>
auto cbegin(const C& container)->decltype(std::begin(container))
{
	return std::begin(container);
}


// you're surprised to see that non-member cbegin doesn't call member cbegin, aren't you?
// so was I.

// but follow the logic. This cbegin template accepts any type of argument
// representing a container-like data structure, C, and it accesses this argument
// through its reference-to-const parameter, container.
// If C is a conventional container type (e.g, a std::vector<T>), 'container' will be
// a reference to a cont version of that container (e.g., const std::vector<T>&). Invoking
// the non-member begin function (provided by C++11) on a const container yields a 
// const_iterator, and that iterator is what this template returns.

// The advantage of implementing things this way is that it works even for containers that offer a begin
// member function (which for containers, is what C++11's non-member begin calls),
// but fail to offer cbegin member. you can thus use this non-member cbegin on
// containers that directly support only begin.


int main()
{
	example_1();
	example_2();

}




