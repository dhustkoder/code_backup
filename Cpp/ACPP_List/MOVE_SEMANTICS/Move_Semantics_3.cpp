#include <iostream>
#include <vector>


// For classes made up of other classes (via either containment or inheritance), the move constructor,
// and move assignment can easily be coded using the std::move
class Base
{
public:
	Base() = default;
	Base(Base&& x)
	{

	}
};


class Derived : public Base
{
	std::vector<int> vec;
	std::string name;
public:
	//...
	//move semantics
	Derived() = default;
	Derived(Derived &&x)	: 
		Base(std::move(x)), // pass by Rvalue reference to Base(Base&&)
		vec(std::move(x.vec)),// move de x.vec to this->vec
		name(std::move(x.name))// move the x.name to this->name
	{

	}
};



int main()
{
	Derived A, B(std::move(A));

}