#include <iostream>
// Koenic Lookup Exemplo 3

namespace A
{
	struct X{};

	void g(X x) { std::cout << "accessing A::g" << std::endl;  }
}



namespace C
{
	void g(A::X x) { std::cout << "accessing C::g" << std::endl; }

	void j()
	{
		A::X x;
		g(x); // this is ambiguos , cuz  the compiler sees the g in this namespace scope, and the other g in namespace A
		// due to Koenic Lookup
	}
}


int main()
{
	C::j();
}