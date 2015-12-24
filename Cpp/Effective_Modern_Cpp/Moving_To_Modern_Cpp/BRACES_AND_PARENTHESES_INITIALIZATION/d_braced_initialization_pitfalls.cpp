#include <iostream>
#define LOG(x) std::cout << x << std::endl


int main()
{


	// The drawback to braced initialization is
	// the sometimes-surprising behavior that
	// braced initializers, std::initializer_list
	// and constructor overload resolution.

	// Their iterations can lead to code that seems like it should do one thing, 
	// but actually does another.

	// In constructor calls for example, braced initializer and parentheses have the same meaning
	// as long as std::initializer_list parameter are not involved.


	struct Widget
	{
		Widget(int i, bool b) { LOG("Widget ctor: int, bool");}
		Widget(int i, double d) { LOG("Widget ctor: int, double"); }
		
	};

	Widget w1(10, true);    // calls first ctor
	Widget w2{10, false};   // also calls first ctor

	Widget w3(10, 10.5);    // calls second ctor
	Widget w4{10, 5.5};     // also calls second ctor

	// so it works very well.
	
	// However if one or more constructors declare a parametr of type std::initializer_list
	// calls using braced initialization syntax strongly prefer the overloads taking - 
	// std::initializer_list

	struct Test
	{
		Test(int i, bool b) { LOG("Test ctor: int, bool");}
		Test(int i, double d) { LOG("Test ctor: int, double"); }
		
		Test(std::initializer_list<long double> il) { LOG("Test ctor: initializer_list");}
	};

	Test t1(10,true); // calls the int i, bool b ctor
	Test t2{10,true}; // calls the initializer_list ctor
	
	Test t3(10,10.5); // calls the int i, double d ctor
	Test t4{10,10.5}; // calls the initializer_list ctor


	// Test t2 and t4 both call the new constructor, the std::initinalizer_list one
	// event though the type of the std::initializer_list constructors, a worse match for both arguments
	



	// and it gets worse... 
	// even what would normally be copy and move construction can be hijacked by std::initializer_list constructors
	
	struct Test_t
	{
		Test_t(int i, bool b) { LOG("Test_t ctor: int, bool");}
		Test_t(int i, double d) { LOG("Test_t ctor: int, double"); }
		
		Test_t(std::initializer_list<long double> il) { LOG("Test_t ctor: initializer_list");}
		
		
		Test_t(const Test_t&) { LOG("Test_t Copy ctor called"); }
	
		operator float() const { return 5.5; }
		
		
	};

	Test_t tt1 (10,true); // ok, first ctor;

	Test_t tt2 {tt1};   // cuz of operator float, tt1 is converted to float then converted to long double to fit
			    // the initializer_list

	// in my clang 3.7.0   this calls the Copy constructor as wanted

	// but my gcc 5.2.0    stills converts to float then to long double in initializer_list

}
