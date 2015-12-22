#include <iostream>

#define LOG(x) std::cout << x << std::endl

//is_type
template<class T>
struct is_type
{
	using type = T;
};


// true/false type
struct true_type
{
	static constexpr bool value = true;
};

struct false_type
{
	static constexpr bool value = false;
};

// IF
template<bool cond, class T, class F>
struct IF : is_type<T>{};

template<class T, class F>
struct IF<false, T, F> : is_type<F>{};


// is_const
template<class T>
struct is_const : false_type
{
};

template<class T>
struct is_const<const T> : true_type
{
};





int main() 
{
	const int x = 0;
	int j;
	is_const<decltype(j)>::value;
	is_const<decltype(x)>::value;

	IF<is_const<decltype(x)>::value, decltype(j), decltype(x)>::type var;
}




