#include <iostream>
#include <string>
#include <memory>





/* Default and Custom deleters */
class Dog{
public:
	Dog(std::string name = "nameless") : m_name(name) { std::cout << "Dog Constructed " << m_name << std::endl; }
	void bark() { std::cout << m_name << " Barked" << std::endl; }
	~Dog() { std::cout << "Dog Destroyed " << m_name << std::endl; }
private:
	std::string m_name;
};

void foo()
{
	// when declaring a smart pointer like this
	// std::shared_ptr<Dog> dPtr(new Dog()); // this is using the default deleter

	// but if I do:
	std::shared_ptr<Dog> dPtr(new Dog("doggy 1"), 
		[](Dog *dog) {std::cout << "custom deleter for dog " << std::endl; delete dog; });
	// here I've defined a custom deleter using a lambda function.

	dPtr->bark();

	// this is useful if we want arrays
	dPtr.reset(new Dog[5],
		[](Dog *dogArr) { std::cout << "deleting array of dogs" << std::endl; delete[] dogArr; });

}


int main()
{
	foo();

}