#include <iostream>
#define LOG(x) std::cout << x << std::endl





template<typename T>
typename std::enable_if<std::is_same<T, int&&>::value,void>::type
printType(){
	LOG("ParamType Is Rvalue reference to an int ( int&& )");
}
template<typename T>
typename std::enable_if<std::is_same<T,int&>::value,void>::type
printType(){
	LOG("ParamType Is Lvalue reference to an int ( int& )");
}

template<typename T>
typename std::enable_if<std::is_same<T,const int&>::value,void>::type
printType(){
	LOG("ParamType Is const Lvalue reference to an int ( const int& )");
}

template<typename T>
typename std::enable_if<std::is_same<T,const int&&>::value,void>::type
printType(){
	LOG("ParamType Is const Rvalue reference to an int ( const int&& )");
}






template<typename T>
void foo(T&& param)
{
	printType<decltype(param)>();
}


int main(){
	auto x = 0;
	const auto cx = x;
	const auto& rx = x;

	foo(30);  // 30 is rvalue int, T is int,       ParamType is int&&
	foo(x);   // x is lvalue int,  T is int,       ParamType is int&
	foo(cx);  // cx is const int,  T is const int, ParamType is const int&
	foo(rx);  // rx is const int&, T is const int, ParamType is const int&
	
	foo(std::move(x));  // after move x is int&&,          T is int,       ParamType is int&&
	foo(std::move(cx)); // after move cx is const int&&,   T is const int, ParamType is const int&&     
	foo(std::move(rx)); // after move rx is const int&&,   T is const int, ParamType is const int&&

}
