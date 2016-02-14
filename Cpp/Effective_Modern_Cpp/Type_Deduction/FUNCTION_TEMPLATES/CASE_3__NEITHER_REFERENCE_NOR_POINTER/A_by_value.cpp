#include <iostream>
#define LOG(x) std::cout << x << std::endl




// When ParamType is Neither a Pointer nor a Reference we're dealing
// with pass-by-value:

template<typename T>
void foo(T param)  // param is passed by value
{
	// The fact that param will be a new object motivates the rules
	// that govern how T is deduced from expr

	// 1 as before, if expr's type is a reference, ignore the reference part.
	// 2 If, after ignoring expr's reference-ness, expr is const, ignore that too. If
	// its volatile, also ignore that. (volatile objects are uncommon. They're generally
	// used only to implementing device drivers.)

}


int main(){
	int x = 42;
	const int cx = x;
	const int& rx = x;
	foo(x);          // T and ParamType are both int
	foo(cx);         // T and ParamType are again both int
	foo(rx);         // T and ParamType are still both int

	// 'param' is an object thats completely independent of CX and RX-- a copy
	// of cx or rx. The fact that cx and rx can't be modified says nothing about whether
	// 'param' can be. Thats why expr's constness (and volatileness. if any) is ignored
	// when deducing a type for param.

}