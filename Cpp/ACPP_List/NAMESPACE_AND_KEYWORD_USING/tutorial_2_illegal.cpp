#include <iostream>




// illegal states with using directive or using declaration


class Base
{
public:
	void foo(const int hex)
	{
		using std::cout; // using delcaration of std::cout
		using std::endl; // using declaration of std::endl

		
		cout << "you passed: " << std::hex << hex << endl;
	}
};



class Derived : public Base
{
public:
	using Base::foo; // using declaration of Base::foo, so Derived::foo does not hide the overloaded function

	void foo()
	{
		using namespace std;// all std members can be used for this scope without "std" qualifier
		std::cout << "foo with no arguments " << endl;
	}

	// ILLEGAL
	using std::cout;		// using declaration of namespace member in a class scope is illegal
	using namespace std;	// using directive in a class scope is also illegal

};

//ILLEGAL
using Derived::foo; // using declaration of  class member out of relative classes scope is also illegal
