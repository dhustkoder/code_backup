#include <iostream>



// Anonymus Namespace: a namespace without a name


void G()
{
	std::cout << "global G" << std::endl;
}

namespace
{
	void G()
	{
		std::cout << "hidden G" << std::endl;
	}
	void hidden_foo()
	{
		// this function can only be accessed in this file
		// this is like declaring a static function
		// but with a benefit

		G(); // this will call the anonymus namespace's version of G, not the global

	}
}

static void hidden_in_this_file()
{
	::G(); // this will call global G
}


int main()
{
	hidden_foo(); // this calls the anonymus namespace hidden foo, which calls anonymus namespace G
	
	hidden_in_this_file(); // calls the static function which calls global G
}