#include <iostream>

// Koenic Lookup


// Exemplo 1



namespace A
{
	struct X{};

	void g(X x){}
}


int main()
{
	A::X x;

	A::g(x); // ok a code as expected


	g(x); // wow but this compiles too.

	// g(x) whithout the A:: qualifier compiles becouse of Koenic Lookup also called Argument Dependent Lookup (ADL)

	// the compiler look for the function "g" not only in  the global scope, 
	// but also in the scope where its parameters are defined (namespace A).
}