#include <iostream>
#include <string>


// Casting can be sometimes, a hacktool (dangerous)

class Dog
{
public:
	Dog(std::string name) : m_name (name){}
	void bark() const  // const function bark, this function cant modify data members or call a non const function... BUT
	{
		const_cast<Dog*>(this)->m_name = "jack"; // if we use const_cast, we hacked into the class and can modify the data member
		std::cout << "woof, my name is " << m_name << std::endl;	
	}

private:
	std::string m_name;

};

int main()
{
	Dog d = std::string("BArao") ;

	d.bark();

}
