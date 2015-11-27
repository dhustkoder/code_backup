#include <iostream>


// exemplo 2


class C
{
public:
	struct Y{};
	static void foo(Y y)
	{
		// So, does the Koenic Lookup works with classes ?
	}
};





int main(void)
{
	C::Y y;
	foo(y); // error, Koenic Lookup only apply to namespaces.

	C::foo(y); // correct
}