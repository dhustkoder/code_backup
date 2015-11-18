#include <iostream>
#include <string>
#include <memory>
#define LOG(x) std::cout << x << std::endl



/*	RAII Preventing Memory Leak when throwing Exceptions from constructor or Try scope.

	then using RAII can really save the DAY...

	as we can see, using smart pointers for doing RAII make our work very easier when dealing with exceptions

	even when exception is throw from the unexpected function the memory will me freed.
	
*/


class Dog
{

public:
	Dog(std::string name) : m_name(name) {
		LOG("Dog " << name << ", is Created");
	}
	void bark() {
		LOG("Dog " << m_name << ", is Barking!!");
	}
	~Dog() {
		LOG("Dog " << m_name << ", is Destroyed...");
	}

private:
	std::string m_name;
};


class DogHouse
{
#define messSize 0xFFFF
public:
	DogHouse(std::string ownerName) 
		: dog(std::make_unique<Dog>(ownerName)), mess(new long double[messSize]) 
	{
		LOG("Dog House is Created");
		for (size_t i = 0; i < messSize; ++i)
			mess[i] = 0;

		bool errorCondition = false;
	
		if (errorCondition)
			throw std::bad_alloc();
	}

	~DogHouse(){
		LOG("Dog House is Destroyed");
	}
private:
	std::unique_ptr<Dog> dog;
	std::unique_ptr<long double[]> mess;
};



void exception_function()
{
	throw std::exception("some unknow error");
}



void exceptions_with_smart_pointer_RAII() {

	try {
		std::unique_ptr<DogHouse> keep = std::make_unique<DogHouse>("DogMeat");
		/* ... do stuff ... */
		bool errorCondition = true;

		if (errorCondition) {
			throw std::exception("unknow error ocurred");
		}

		exception_function(); // memory will not leak, keep is destroyed in the end of scope as his members.


	}

	catch (std::exception &err) {
		LOG(err.what());
	}

}

int main()
{
	for (size_t i = 0; i < 0xFF; ++i)
	{
		exceptions_with_smart_pointer_RAII();
	}
	std::cin.ignore();
}