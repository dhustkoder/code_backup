#include <iostream>
#define LOG(x) std::cout << x << std::endl;





// What Happens When we have Inheritance, and try to delete a Derived class from Base class pointer, which
// operators new and delete we might call ?


// Well, the YellowDog operator new will be called when we allocate YellowDog, But The Destructor and operator delete
// will be called for Dog
class Dog
{
public:
	Dog() { LOG("Constructing a Dog!"); }

	inline
	static void * operator new(std::size_t size) noexcept
	{
		void *pMemory = std::malloc(size);
		if (pMemory)
			return pMemory;
		else
			return nullptr;

	}

	inline
	static void operator delete(void *block) noexcept
	{
		LOG("Freeing Dog")
		std::free(block);
	}

	virtual ~Dog() { LOG("Destroying a Dog"); }
	// But if we declare the Base Class destructor as virtual
	// it will call the YellowDog destructor, and magicaly calls YellowDog's operator delete.
};




class YellowDog : public Dog
{
public:
	YellowDog() { LOG("Constructing YellowDog"); }


	inline
	static void * operator new(std::size_t size) noexcept
	{
		void *pMemory = std::malloc(size);
		if (pMemory)
			return pMemory;
		else
			return nullptr;

	}

		inline
	static void operator delete(void *block) noexcept
	{
		LOG("Freeing YellowDog");
		std::free(block);
	}

	~YellowDog() { LOG("Destroying Yellow Dog"); }
};





int main(void)
{
	// as long you create custom operators new for each class, or 1 operator new in the base class, that knows the 
	// object that he is going to allocate using condition like:
	std::size_t size;
	if (size == sizeof(Dog))
		/* allocate dog */;
	else if (size == sizeof(YellowDog))
		/*Allocate YellowDog*/;

	// it can work,  and don't forget to declare the Base Class destructor as virtual for calling the Derived destructor
	// and if there is a Derived operator delete, it will be called too.
	
	Dog *py = new YellowDog(); // calls the operator new of YellowDog, and construct YellowDog normaly


	delete py; // due to Dog's destructor being declared virtual ~Dog() {...}, it will call the YellowDog destructor
	// and will call the YellowDog operator delete as we want.
}