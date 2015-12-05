#include <iostream>
#include <string>
#define LOG(x) std::cout << x << std::endl



template< class ...R >
struct last_element;


template<class T>
struct last_element<T> { using type = T; };


template<class T, class ...R>
struct last_element<T, R...>
{
	using type = typename last_element<R...>::type;
};


int main() {

	last_element<int, std::string, char>::type r;




}