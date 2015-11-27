#include <iostream>
#include <string>
#include <memory>
#define LOG(x) std::cout << x << std::endl

// Using a factory function with unique_ptr...

class Dog
{
public:
	static std::unique_ptr<Dog> DogFactory(std::string name) {
		return std::move(std::unique_ptr<Dog>(new Dog(name)));
	}
	void bark() {
		LOG("Dog: " << m_name << ", is barking!!");
	}

	~Dog() {
		LOG("Destroying Dog: " << m_name);
	}
private:
	std::string m_name;
	
	Dog(std::string name) : m_name(name) {
		LOG("Creating Dog: " << name);
	}

};



void example_1()
{
	// as we see, it is totaly fine.
	std::unique_ptr<Dog> dogMeat = Dog::DogFactory("DogMeat");

	// what if we want to get the a raw pointer from the unique_ptr and delete it ourselves ?
	Dog *rawD = dogMeat.release();

	// now dogMeat is == nullptr, and we must delete the dog.


	// what if we want to give the rawPtr back to unique_ptr ?

	dogMeat.reset(rawD); // now dogMeat is back in controll



}


int main()
{
	example_1();
}
