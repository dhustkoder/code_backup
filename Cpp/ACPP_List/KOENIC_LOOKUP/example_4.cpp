#include <iostream>



// Koenic Lookup example 4



namespace A
{
	struct X {};
	void g(A::X x)
	{
		std::cout << "calling A::g" << std::endl;
	}
}



// but what if namespace C were a class

class C
{
public:
	void g(A::X x) { std::cout << "calling C::g" << std::endl;  }

	void j()
	{
		A::X x;
		g(x); // this will compile alright now, cuz the compiler gives priority to class member functions and call C::g
	}
};



int main()
{
	C c;
	c.j;
}