#include <iostream>


// Koenic Lookup Namespace Design - Theorotical Reason.

	// -What is the interface of a class ?


namespace A
{
	class C
	{
	public:
		void f() = 0;
		void g() = 0;
	};

	void h(C) {}; // is h part of C's interface ?

	std::ostream& operator<<(std::ostream& os, C c) {  }; // is operator << part of C's interface ??
}


void j(A::C c) {}; // now this is part of C's interface? no, this is more like a client function that operates with C


// Engineering Principle:
//
//	1. Functions that operates on C, in the same namespace of C, are part of C's interface
//
//	2. Functions that are part of C's interface, should be in the same namespace of C
//


// take a look at this

namespace D
{
	class F{};
	int operator+(int x, D::F f) { return x + 1; } // right place to put, Koenic Lookup does the job, everyone is happy
}

int operator+(int x, D::F f) { return x + 1; } // WRONG PLACE TO PUT, accumulate will not compile


namespace std
{
	template <class InputIterator, class T>
	T accumulate(InputIterator first, InputIterator last, T init)
	{
		while (first != last)
			init = init + *first++;

		return init;
	}
}




int main()
{
	D::F f[4];

	std::accumulate(f, f + 4, 0);

	// as you see the function in std accumulate will use operator + on F, if operator+ is outside the namespace , 
	// the compiler will not use the correct function operator to call, because it uses Koenic Lookup, so put
	// the operator+ function that operates on C with the same namespace as class C
}

