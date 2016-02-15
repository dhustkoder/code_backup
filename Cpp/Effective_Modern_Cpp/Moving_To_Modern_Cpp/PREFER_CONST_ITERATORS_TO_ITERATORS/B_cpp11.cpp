#include <iostream>
#include <vector>
#include <algorithm>
#include <boost/type_index.hpp>


int main()
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
