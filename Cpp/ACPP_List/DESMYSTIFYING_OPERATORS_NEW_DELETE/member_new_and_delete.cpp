#include <iostream>
#include <string>



class Dog
{
public:
// ....
	Dog() // default
	{
		//std::cout << "default Dog constructor [" << this << "]" <<  std::endl;
	}

	Dog(int x)  // int argument
	{
		std::cout << "dog constructor int " << x << "[" << this << "]" << std::endl;
	}

	Dog(const std::string& word) // std::string argument
	{
		std::cout << "dog constructor std::string: " << word << " ["<< this << "]" << std::endl;
	}

	Dog(std::string &&word) // rvalue string argument
	{
		std::cout << "dog constructor std::string&& rvalue: " << word << " [" << this << "]" << std::endl;
	}


	// custom operator new
	static void *operator new(std::size_t size) noexcept // for default constructor
	{
		void *memory = malloc(size); // allocate memory
		if (memory) // if allocate ok
			return memory; // returns
			
		else
			return nullptr;
		
	}

	static void *operator new[](std::size_t size) noexcept
	{
		void *memory = malloc(size); // allocate memory
		if (memory) // if allocate ok
			return memory; // returns
			
		else
			return nullptr;
	}

	static void operator delete(void *block) noexcept
	{
		free(block);
	}

	static void operator delete[](void *block) noexcept
	{
		free(block);
	}

	~Dog() 
	{ 
		//std::cout << "destructor " << std::endl;  
	}
};



int main(void)
{

	Dog *d1 = new Dog[10]; 
	// Enters the member operator new, then after it returns , construct all 10 objects

	Dog *d2 = new Dog("const char * argument"); 
	// enters the member new, then after it returns call constructor std::string&&

	delete[] d1; // call destructor on all objects, then enters the member operator delete[] from Dog
	delete d2; // call destructor , then enters the member operator delete;
	

}