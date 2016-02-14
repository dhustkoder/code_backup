#include <iostream>
#include <typeinfo>
// Template Meta-Programming C++ 
// Diving in....

// Compile-Time decision making

template<class T>
struct type_is
{
	using type = T;
};


// Imagine a metafunction, IF/IF_t, to select one of 2 types:
template<bool condition, class T, class F>
struct IF : type_is<T> 
{

};

// the specialization that handles the false case
template<class T,class F>
struct IF<false, T, F> : type_is<F>
{

};

// a helper IF_t to make things simple
template<bool condition, class T, class F>
using IF_t = typename IF<condition, T, F>::type;




void IF_EXAMPLE()
{
	IF_t<(sizeof(int) >  4), int, uint> variable;
	
	std::cout << typeid(variable).name() << std::endl;
	
	
	
	// Such a facility would let us write self-configuting class
}

// AND this can be aplied to inheritance



class Base1
{
public:
	Base1(){
		printf("Inheritance from Base1\n");
	}
};


class Base2
{
public:
	Base2(){
		printf("Inheritance from Base2\n");
	}
};


template<int x>
class SomeClass : public IF_t<(x > 10), Base1, Base2>
{

};





int main()
{
	IF_EXAMPLE();
	SomeClass<11> base_1_;
	SomeClass<10> base_2_;	
	
	
}
