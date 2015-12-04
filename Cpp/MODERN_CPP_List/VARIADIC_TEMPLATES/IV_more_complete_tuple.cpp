#include <iostream>
#include <string>
#define LOG(x) std::cout << x << std::endl


template<typename ...Ttypes> struct Tuple; // Declaration

template<> class Tuple<> { /* empty */};


template<typename Tvalue, typename ...Trest>
struct Tuple<Tvalue, Trest...> : Tuple<Trest...>
{
	Tvalue data;
};


int main() 
{
	
	
}