#include <iostream>
// Namespace and Keyword "using"


// C++ Keyword: using

// 1. using directive: Brings all namespace members into current scope

//	example:
//using namespace std; // now we can use all members into namespace std; without std qualifier ( std::cout ) goes ( cout )



// 2. using declaration: 
		// a. Bring one specific namespace member to current scope.
		// b. Bring a member from base class to current class's scope

class Base
{
public:
	void foo(const int hex) 
	{
		using std::cout; // now "std::cout" , into this function can be used as "cout", this is using declaration a.
		using std::endl; // now "std::endl" can be used as (endl)
		// these 2 are = Using Declaration, and work only in the scope of this function

		// if we had used
		//using namespace std; // hex  can go ambiguos, we want std::hex, and argument hex
		
		cout << "you passed hex: " << std::hex << std::uppercase << hex << endl;
		// so std::hex need the namespace std:: to work
	}
}; 



class Derived : public Base
{
public:
	using Base::foo; //  in order to use Base foo, we need to do using declaration, cuz the Derived foo ,does a name hiding of Base foo.
	// so now Base::foo is usable from Derived objects


	void foo() // so we have an overload foo, the foo(const int) from Base , and foo() from Derived
	{
		using namespace std; // this is Using Directive, all members in std;
		cout << "foo without argument" << endl;
	}
};

int main(void)
{
	Derived der;
	der.foo(); // normal foo from Derived
	der.foo(0xBAB); // overload foo with const int argument
}




