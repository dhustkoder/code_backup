#include <iostream>
#define LOG(x) std::cout << x << std::endl



// int
template<typename T>
typename std::enable_if<std::is_same<T,int>::value,void>::type
printType(const char *msg){
	LOG( msg << " Is int ( int )");
}

// const int
template<typename T>
typename std::enable_if<std::is_same<T,const int>::value,void>::type
printType(const char *msg){
	LOG( msg << " Is const int ( const int )");
}



//Lvalue ref
template<typename T>
typename std::enable_if<std::is_same<T,int&>::value,void>::type
printType(const char *msg){
	LOG( msg << " Is Lvalue reference to an int ( int& )");
}


//Rvalue ref
template<typename T>
typename std::enable_if<std::is_same<T, int&&>::value,void>::type
printType(const char *msg){
	LOG( msg << " Is Rvalue reference to an int ( int&& )");
}


// const Lvalue ref
template<typename T>
typename std::enable_if<std::is_same<T,const int&>::value,void>::type
printType(const char* msg){
	LOG( msg << " Is const Lvalue reference to an int ( const int& )");
}
// const Rvalue ref
template<typename T>
typename std::enable_if<std::is_same<T,const int&&>::value,void>::type
printType(const char* msg){
	LOG(msg << " Is const Rvalue reference to an int ( const int&& )");
}






template<typename T>
void foo(T&& param)
{
	LOG("\t -----");
	printType<T>("T");
	printType<decltype(param)>("ParamType");
}


int main()
{
	int x = 0;
	const int cx = x;
	const int& rx = x;

	foo(30);  // 30 is rvalue int, T is int,         ParamType is int&&
	foo(x);   // x is lvalue int,  T is int&,        ParamType is also int&
	foo(cx);  // cx is const int,  T is const int&,  ParamType is also const int&
	foo(rx);  // rx is const int&, T is const int&,  ParamType is also const int&
	
	foo(std::move(x));  // after move x is int&&,          T is int,       ParamType is int&&
	foo(std::move(cx)); // after move cx is const int&&,   T is const int, ParamType is const int&&     
	foo(std::move(rx)); // after move rx is const int&&,   T is const int, ParamType is const int&&

}
