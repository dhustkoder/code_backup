#include <iostream>
#include <string>
#include <memory>



/* std::shared_ptr, defined in header <memory> ,

	is a smart pointer that  retains shared ownership of an object through a pointer. 
	Several shared_ptr objects may own the same object. 
	The object is destroyed and its memory deallocated when either of the following happens:

		1. the last remaining shared_ptr owning the object is destroyed.
		2. the last remaining shared_ptr owning the object is assigned another pointer via operator= or reset().

	and when using smart pointers, you can use casts for them:

		1. std::static_pointer_cast
		2. std::dynamic_pointer_cast
		3. std::const_pointer_cast

*/

class Dog
{
public:
	Dog(std::string name) : m_name(name) { std::cout << "Dog " << name << " is Created!" << std::endl; }
	void bark() { std::cout << "Dog " << m_name << " is barking!" << std::endl; }
	~Dog() { std::cout << "Destroying Dog: " << m_name <<  std::endl; }
private:
	std::string m_name;
};




void foo()
{
	std::shared_ptr<Dog> dPtr(new Dog("Dog1")); // a shared pointer of type Dog is created.
	dPtr->bark();

	std::cout << dPtr.use_count() << std::endl; // 1

	{
		std::shared_ptr<Dog> dPtr2 = dPtr;
		std::cout << dPtr.use_count() << std::endl; // 2
		dPtr2->bark();
	} // dPtr2 goes out of scope, but doesn't destroy the dog cuz another shared_ptr has it.

	std::cout << dPtr.use_count() << std::endl; // 1 again
	
	dPtr->bark();
	// at the end of the function the Dog in dPtr is destroyed.
}


void foo2()
{
	
	// although we can initialize a shared_ptr like this:
	// std::shared_ptr<Dog> dPtr(new Dog());

	// there is a faster and safer (exception safer) way
	std::shared_ptr<Dog> dPtr = std::make_shared<Dog>("New Doggy");
	// we give the arguments for Dog's constructor directly to make_shared.
	dPtr->bark();

	// and we can assign from raw pointers too.
	Dog *dp = new Dog("doggy 2");
	dPtr.reset(dp);// here, the "New Doggy" is destroyed, and dPtr is assign with a new object "doggy 2"
	dPtr->bark();
	// but using raw pointers like this is not a good idea mixing with smart pointers
	// it is better to immediatly assign the new object to the smart pointer.
	

}


int main()
{
	foo();
	foo2();
}