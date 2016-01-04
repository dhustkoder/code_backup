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



// repeat the last type,
// for msvc paring do not subline
// foo<int> as an error
template<class T>
typename std::enable_if<is_one_of<T, float, int, int>::value, void>::type
foo();

// as we do not implement a foo<T> ( foo for any generic type) foo will only compile as
// foo<int> and foo<float>, that we implemented in the compilation unit



#endif
