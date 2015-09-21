#include <iostream>
#include <typeinfo>
class Dog
{
friend std::ostream& operator<<(std::ostream &os, Dog &dog)
{
	std::cout << "This is a dog named: " << dog.name_ << std::endl; 
} 
public:
	Dog(std::string name) :
		name_ ( name ) {}
private:
	std::string name_;

};


class YellowDog : public Dog
{
public:
	YellowDog(std::string name) :
		Dog(name) {}


};

class Test
{
public:
~Test()
{
	std::cout << "DESTROYED TEST" << std::endl;
}
};



int main()
{
	// Type Conversion:
	// 
	// 1. Implicit Type Conversion
	// 2. Explicit Type Conversion - Casting



	// 1. Static cast

	int i = 10;

	float f = static_cast<float>(i); // convert one type to another

	Dog dog1 = static_cast<Dog> (std::string("Diamond Dog")); // this type conversion needs to be defined in the constructor of dog to initialize it in this way.
															// constructor without keyword "explicit"

	Dog* dog2 = static_cast<Dog*>(new YellowDog("Patric")); // convert pointer/reference from one type to a related type (up/down casting)



	std::cout << dog1 << std::endl;
	std::cout << *dog2 << std::endl; // this will enter the same friend function as the dog1, cause is casted to a Dog* pointer...

	Test t = static_cast<Test>(*(new Test)); // cool, the Test is destroyed in end of scope...
	









}














