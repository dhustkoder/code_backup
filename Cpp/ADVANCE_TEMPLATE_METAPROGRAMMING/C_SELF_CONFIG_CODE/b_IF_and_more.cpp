#include <iostream>
#define LOG(x) std::cout << x << std::endl
template<class T>
struct is_type{ using type = T;};

struct false_type { static constexpr bool value = false; };
struct true_type { static constexpr bool value = true; };

template<bool cond, class T, class F>
struct IF : is_type<T>{};

template<class T, class F>
struct IF<false, T, F> : is_type<F>{};


template<class T>
struct is_const : false_type{};

template<class T>
struct is_const<const T> : true_type{};








int main(int argc, char *argv[])
{
	IF<sizeof(int) == 8, int, long long>::type greatInt; // cool

	int x = 0;
	const int y = 0;

	IF<is_const<decltype(y)>::value, decltype(x), decltype(y)>::type non_const = 10;

	non_const = 20;



}
