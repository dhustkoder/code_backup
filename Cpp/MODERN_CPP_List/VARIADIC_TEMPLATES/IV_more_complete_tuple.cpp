#include <iostream>
#include <string>
#define LOG(x) std::cout << x << std::endl



template<int idx, class ...Ts>
struct tup_elem {};


template<>
struct tup_elem<-1>
{

};


template< int idx, class T, class ...Ts>
struct tup_elem : tup_elem<idx - 1, Ts...>
{
	T data;
};

int main() 
{




}