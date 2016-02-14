#include <iostream>
#define LOG(x) std::cout << x << std::endl



// ENABLE_IF, A single-type variant on conditional


// IF true give back the givin type, if false give nothin


// first the helper

template<class T>
struct type_is { using type = T; };


// now the enable_if

// this first declaration assumes that condition is true
template<bool, class T>
struct enable_if : type_is<T> {};



// now the specialization for false

template<class T>
struct enable_if<false,T> {}; // no type at all



// how this helps ?
template<class T>
typename enable_if<std::is_integral<T>::value, long long>::type 
work(T t)
{
	LOG("this shit is integral");
	return 0;
}

template<class T>
typename enable_if<std::is_floating_point<T>::value, long double>::type 
work(T t)
{
	LOG("this shit is floating point");
	return 0;
}




int main()
{

	double x = 2.3;
	float y = 3.3;
	unsigned z = 20;
	int h = 30;

	work(x);
	work(y);
	work(z);
	work(h);






}
