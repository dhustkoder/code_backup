#ifndef TEMPLATE_FUNCTIONS_H
#define TEMPLATE_FUNCTIONS_H
#include <iostream>
#define LOG(x) std::cout << x << std::endl

template<class ...Ts>
struct is_one_of;


template<class T>
struct is_one_of<T> : std::false_type
{

};

template<class T, class ...Ts>
struct is_one_of<T, T, Ts...> : std::true_type
{

};


template<class T, class T2, class ...Ts>
struct is_one_of<T, T2, Ts...> : is_one_of<T, Ts...>
{

};



template<class T>
typename std::enable_if<is_one_of<T, float, int>::value, void>::type
foo();




#endif
