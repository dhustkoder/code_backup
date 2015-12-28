#include <iostream>
#define LOG(x) std::cout << x << std::endl



//as before
template<typename T>
void foo(T& param){ // param is a const reference
	LOG("is T const? " << std::boolalpha << std::is_const<T>::value);
	LOG("is ParamType const? " << std::boolalpha << std::is_const<decltype(param)>::value);
}



// NOTE that I added const to ParamType
template<typename T>
void foo_2(const T& param){ // param is a const reference
	LOG("is T const? " << std::boolalpha << std::is_const<T>::value);
	LOG("is ParamType const? " << std::boolalpha << std::is_const<decltype(param)>::value);
}


int main(){
	int x          = 27;  // as before
	const int cx   = x;   // as before
	const int& crx = x;   // as before

	foo(x);               // T is int, ParamType is int&
	foo(cx);              // T is const int, ParamType is const int&
	foo(crx);             // T is const int, ParamType is const int&
	
	LOG("/*...*/");
	
	foo_2(x);               // T is int, ParamType is CONST int&
	foo_2(cx);              // T is INT, ParamType is CONST int&
	foo_2(crx);             // T is INT, ParamType is CONST int&

	// that means that T's type depends on ParamType
}

