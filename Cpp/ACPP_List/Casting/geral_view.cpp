#include <iostream>
#include <typeinfo>
class Dog
{
friend std::ostream& operator<<(std::ostream &os, Dog &dog)
{
	std::cout << "This is a dog named: " << dog.name_ << std::endl; 
	return os;
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
	void imYellow(){ std::cout << "Im Yellow" << std::endl; };

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



	// 1. Static_Cast
	// the static_cast can work on all types, as long as type conversion is defined for those types...

	int i = 10;

	float f = static_cast<float>(i); // convert one type to another

	Dog dog1 = static_cast<Dog> (std::string("Diamond Dog")); // this type conversion needs to be defined in the constructor of dog to initialize it in this way.
															// constructor without keyword "explicit"

	Dog* dog2 = static_cast<Dog*>(new YellowDog("Patric")); // convert pointer/reference from one type to a related type (up/down casting)

	//dog2->imYellow(); // doesn't work now
	static_cast<YellowDog*>(dog2)->imYellow(); // now it works...
	// also works for a type that is not intended to be YellowDog... 
	static_cast<YellowDog*>( & dog1 )->imYellow(); // so becareful, you might fuck your code up. if starts throwing pointers and casts between related types


	std::cout << dog1 << std::endl;
	std::cout << *dog2 << std::endl; // this will enter the same friend function as the dog1, cause is casted to a Dog* pointer...
	

	{
		Test *ptr = new Test;
		Test t = static_cast<Test>(*(ptr)); // cool, the Test is destroyed in end of scope...
						// but dont be stupid, the Test allocated with new is still there...

	
		delete ptr; // now it really is destroyed
	}



	// 2. Dynamic_Cast
	// the dynamic_cast convert a pointer/reference to a related type (down cast)

	Dog *d3 = new YellowDog("STEAM"); // this is a dynamic_cast, even if im not using the operator.

	YellowDog *d4 = dynamic_cast<YellowDog*>(d3); // doing downcast, casting from base class to derived...

	// dynamic_cast do run-time check, if the types are compatible , d4 == d3, if not d4 == nullptr.

	delete d4;
	delete d3;

	

	




	return 0;

}














