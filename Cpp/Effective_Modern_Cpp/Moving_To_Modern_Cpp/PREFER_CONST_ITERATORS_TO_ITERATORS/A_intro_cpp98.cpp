#include <iostream>
#include <vector>
#include <algorithm>
int main()
{

	// const_iterators are the STL equivalent
	// of pointers-to-const.

	// they point to values that may not be modified

	//the standard practice of sing const whenever possible
	// dictates that you should use const_iterators any
	// time you need an iterator but have no need to modify
	// what these iterators points to



	// thats as true for C++98 as for C++11

	// but in C++98 , const_iterators had only halfhearted support.

	// It wasn't that easy to create them, and once you had one,
	// the ways you could use it were limited. For example.
	// suppose you want to search a std::vector<int>

	// for the first occurrence of 
	// 1983 (the year "C++" replaced "C with classes" as the name of the programming 
	// language)


	// then insert the value 1998 (the year the first ISO C++ standard was adopted)
	// at that location.


	// if there's no 1983 in the vector, the insertion should go at the end of the vector.

	static int vecIni[6] = {1500, 1293, 1983, 2004, 2001, 19999}; // a static array to initialize the vec, (as C++98 do not have initializer_list)
	std::vector<int> vec;
	vec.reserve(6);
	
	for(int i = 0; i < 6; ++i)
		vec.push_back(vecIni[i]);


	std::cout << vec[2] << std::endl;


	std::vector<int>::iterator itr = std::find(vec.begin(), vec.end(), 1983);
	
	vec.insert(itr, 1998);


	std::cout << vec[2] << std::endl;


	// But iterators aren't really the proper choice here, because this code never modifies what
	// an iterator points to. Revising the code to use const_iterators should be trivial;
	// but int C++98 it was anything but. 

	typedef std::vector<int>::const_iterator CItr;
	typedef std::vector<int>::iterator Itr;


	CItr citr = std::find(static_cast<CItr>(vec.begin()), static_cast<CItr>(vec.end()), 1998);
	vec.insert(static_cast<Itr>(citr), 1983); // and does not compile...



	// The typedefs aren't required, of course. But they make the casts easier to read and write.


	
	


}














