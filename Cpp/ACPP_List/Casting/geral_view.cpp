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

	virtual void iAm() { std::cout << "I'm a Dog named: " << this->name_ << std::endl; }
	

	~Dog()
	{
		std::cout << "Dog " << this->name_ << ", destroyed" << std::endl;
	}


protected:
	std::string name_;

};


class YellowDog : public Dog
{
public:
	YellowDog(std::string name) :
		Dog(name) {}

	void iAm()
	{ 
		std::cout << "Im Yellow" << std::endl; 
	}

	~YellowDog()
	{
		std::cout << "YellowDog " << this->name_ << ", Destroyed" << std::endl;
	}
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
	static_cast<YellowDog*>(dog2)->iAm(); // now it works...
	// also works for a type that is not intended to be YellowDog... 
	static_cast<YellowDog*>( & dog1 )->iAm(); // so becareful, you might fuck your code up. if starts throwing pointers and casts between related types


	std::cout << dog1 << std::endl;
	std::cout << *dog2 << std::endl; // this will enter the same friend function as the dog1, cause is casted to a Dog* pointer...
	
	delete dog2;

	{
		Test *ptr = new Test;
		Test t = static_cast<Test>(*(ptr)); // cool, the Test is destroyed in end of scope...
											// but dont be stupid, the Test allocated with new is still there...

	
		delete ptr; // now it really is destroyed
	}



	// 2. Dynamic_Cast


	// the dynamic_cast only work on pointer/reference to a related type (down cast)

	Dog *baseDog = new Dog("BASE DOG");
	Dog *derivedDog = new YellowDog("DERIVED DOG"); // this is a dynamic_cast, even if im not using the operator.

	YellowDog *yellowDog = dynamic_cast<YellowDog*>(derivedDog); // doing downcast, casting from base class to derived...
												  // this works, cause derivedDog points to a YellowDog
	

	YellowDog *yellowDog_2 = dynamic_cast<YellowDog*>(baseDog); // trying to make a Dog* into a  YellowDog* ( derived type), this won't work, 
																//and *yellowDog_2 will point null

	// dynamic_cast do run-time check, if the types are compatible , yellowDog_2 == baseDog, if not yellowDog_2 == nullptr.


	if(yellowDog_2 == nullptr)
		std::cout << "yellowDog_2 is nullptr, dynamic_cast failed" << std::endl;





	delete baseDog;
	delete derivedDog;

	
	return 0;

}













