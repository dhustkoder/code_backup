#include <iostream>
#include <string>
#include <memory>
#define LOG(x) std::cout << x << std::endl



/*	Manual Preventing Memory Leak when throwing Exceptions from constructor or Try scope.


	in this example, I've a DogHouse that holds a heap allocated dog and a heap allocated big array.

	IF: exception is thrown by the constructor of DogHouse the DogHouse destructor will not run later.
	THEN: we have to clean resources in constructor before letting the exception scape from DogHouse's constructor.

	IF: exception is thrown in TRY scope then the later delete will not run.
	THEN: we have to clean resources before leting the exception scape from TRY field.


	BUT: what if a other function called from TRY scope throws some unexpected exception ?

	We could do some work around to fix that, maybe make the function returning a bool for error instead of a exception,
	but that maybe not possible.

	then using RAII can really save the DAY.
	
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
	DogHouse(std::string ownerName) : dog(new Dog(ownerName)), mess(new long double[messSize]) {
		LOG("Dog House is Created");
		
		for(size_t i=0; i < messSize; ++i)
			mess[i] = 0;

		bool errorCondition = false;
		if (errorCondition)
		{
			delete dog; // if exception is thrown, the destructor will not be executed, 
			delete mess;//then we need to delete the allocated members now
			throw std::bad_alloc();
		}
	}
	~DogHouse(){
		LOG("Dog House is Destroyed");
		delete dog;
		delete mess;
	}
private:
	Dog *dog;
	long double *mess;
};




void exception_function()
{
	throw std::exception("some unknow error");
}




void exceptions_without_smart_pointer_RAII() {

	try {
		DogHouse *keep = new DogHouse("DogMeat"); // if exception is thrown by DogHouse constructor, memory will NOT leak.
		/* ... do stuff ... */

		bool errorCondition = true;
		
		if (errorCondition)  // exception thrown by TRY scope , memory still NOT LEAK
		{
			delete keep;// if exception is throw, the delete in the end will not be executed, 
						//then we have to do manualy in error condition
			throw std::exception("unknow error ocurred");
		}

		exception_function(); // unexpected exception thrown by some random method . memory will Leak.


		delete keep; 
	}
	catch (std::exception &err) {
		LOG(err.what());
	}

}

int main()
{
	for (size_t i = 0; i < 0xFF; ++i)
	{
		exceptions_without_smart_pointer_RAII();
	}
	std::cin.ignore();
}