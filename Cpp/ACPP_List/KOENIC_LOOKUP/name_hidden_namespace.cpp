#include <iostream>




/* Name Lookup Sequence
*
*	With namespace:
*
*		current scope => next enclosed scope => ... => global scope
*
*		To override the sequence:
*			1. Qualifier or using declaration.
*			2. Koenic Lookup
*
*		With Classes:
*			current class scope => parent scope => ... => global scope
*
*		To override the sequence:
*			- Qualifier or using declaration
*
*		Name hiding.
*
*
*/




namespace A
{
	struct X {};
	void g(int x) { }

	void f(X x) { }

	namespace C
	{
		using A::g; // done now we can use A::g and C::g as overloaded functions.


		void g() { }
		void f() { }

		void j()
		{
			g(10); // as we see this is hided by this scope's g that take no parameter 
			// how do we overcome name hidding?
			// using declaration!!
			X x;
			f(x); // But what about this ??, with the Koenic Lookup the name hidding is fixed by Koenic Lookup
			// no needing to use using declaration for function A::f;
		}
	}
}


