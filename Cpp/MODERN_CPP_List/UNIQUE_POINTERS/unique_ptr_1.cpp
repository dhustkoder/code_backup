#include <iostream>
#include <string>
#include <memory>
#include <functional>
#define LOG(x) std::cout << x << std::endl;



/* UNIQUE POINTER: 

	std::unique_ptr is a smart pointer that retains SOLE OWNERSHIP of an object,
	through a pointer and destroys that object when the unique_ptr goes out of scope.

	unlike the shared_ptr , unique_ptr are light weight smart pointer.
	having the same size as a normal pointer.

	so, if you don't need multiple owners for  a object reference through a pointer,
	don't use shared_ptr, but std::unique_ptr.
*/



class Dog
{
public:
	Dog(std::string name) : m_name(name) {
		LOG("Creating Dog: " << name);
	}

	void bark() {
		LOG("Dog: " << m_name << ", is barking!!");
	}

	~Dog() {
		LOG("Destroying Dog: " << m_name);
	}
private:
	std::string m_name;
};




void example_1()
{
	std::unique_ptr<Dog> pD = std::make_unique<Dog>("DogMeat");
	std::unique_ptr<Dog> pD2 = std::make_unique<Dog>("D-Dog");

	// std::shared_ptr<Dog> s_ptr = pD; compiler error, can't have multiple owners for unique_ptr content.

	pD->bark();

	pD = std::move(pD2); // now 3 things happen: 
	// 1. DogMeat is destroyed
	// 2. pD2 becomes empty
	// 3. pD now owns D-Dog.


	pD->bark();
}


void example_2()
{
	std::function<void(std::unique_ptr<Dog>)> foo = [](std::unique_ptr<Dog> dog)->void
	{
		dog->bark();
	};

	// does dog get destroyed in lamda "foo" ? or back "to example_2" ?
	std::unique_ptr<Dog> dog1 = std::make_unique<Dog>("D-Dog");
	foo(std::move(dog1));

	if (dog1 == nullptr)
		LOG("D-Dog was destoyed in \"foo\"");
}


int main()
{
	example_2();
}