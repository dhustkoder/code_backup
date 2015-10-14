#include <iostream>
#include <memory>
#include <utility>


class TEST
{
public:
	TEST(std::string name) 	: name_(name) 						{ std::cout << "DEFAULT CONSTRUCTOR" << std::endl; }
	TEST(const TEST& rhsCopy) : name_ (rhsCopy.name_) 			{ std::cout << "COPY CONSTRUCTOR " << std::endl; }
	TEST(TEST&& rhsMove) 	: name_ (std::move(rhsMove.name_))	{ std::cout << "MOVE CONSTRUCTOR" << std::endl; }
	~TEST() 													{ std::cout << "DESTRUCTOR FOR " <<  name_ << std::endl; }
	std::string name_;
};




// OK lets take a look into using Perfect Forwarding with Factory functions




// we need 2 template arguments to make it more simple, you cant return std::shared_ptr<TEST&&> ...
// so the first template is the class itself without any &&, the second you dont need to specify (C++11) it will be
// the type of the argument you passed. with std::move it will be TEST&&, 
template<class T, class A1> 
std::shared_ptr<T> Factory( A1&& Arg ) // so as we know, here is a universal reference of type A1, 
{

	return std::shared_ptr<T>(new T(std::forward<A1>(Arg))); 
	// and here we forward it to construct a new object with the aspects of Arg
	// if Arg is indeed a Rvalue , the new object will be move construct, otherwise will be copy constructed
}



void normalFunction() 
{
	{
		std::shared_ptr<TEST> ptr = Factory<TEST>(TEST("ptr")); // here we got a move constructed.
		std::shared_ptr<TEST> ptr2 = Factory<TEST>(*ptr); // and here we got a copy constructed

	// so the behavior is: ptr is MOVE constructed from Rvalue " TEST() ", and then "TEST()" is destroyed.

	// ptr2 is COPY constructed from lvalue "*ptr". then the braces comes to a end then:
	// ptr2 is destroyed , ptr1 is destroyed
	}
	// now , since our Factory use Templates, we can call default constructor directly!

	std::shared_ptr<TEST> ptr = Factory<TEST>("PTR 1"); // default consruct with this name
	std::shared_ptr<TEST> ptr2 = Factory<TEST>(std::string(ptr->name_.begin(),ptr->name_.end()-1) + "2"); // default 
	// construct with ptr's name but instead of PTR 1 we have PTR 2


	// then the function ends and they get destroyed in reverse of course , ptr2 then ptr.
}



int main()
{
	normalFunction();
	std::cout << "in main again" << std::endl;
}








