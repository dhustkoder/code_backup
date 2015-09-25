#include <iostream>



// Casting can be sometimes, a hacktool (dangerous)


class Dog
{
public:
	Dog(std::string name) : name_ (name){}
	void bark() const  // const function bark, this function cant modify data members or call a non const function... BUT
	{
		const_cast<Dog*>(this)->name_ = "jack"; // if we use const_cast, we hacked into the class and can modify the data member
		std::cout << "woof, my name is " << name_ << std::endl;	
	}

private:
	std::string name_;

};









int main()
{
	Dog d = std::string("BArao") ;

	d.bark();






}
