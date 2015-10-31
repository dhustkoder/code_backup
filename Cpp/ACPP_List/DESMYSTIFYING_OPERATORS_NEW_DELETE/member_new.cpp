#include <iostream>
#include <string>



class Dog
{
public:
	// ....
	Dog() // default
	{
		std::cout << "default Dog constructor [" << this << "]" <<  std::endl;
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
		Dog *ptr = (Dog*)malloc(size); // allocate memory
		if (ptr) // if allocate ok
		{
			::new(ptr) Dog(); // call default constructor on object in memory
			return ptr; // returns
		}
		else
			return nullptr;
		
	}

	template<class T>
	static void * operator new(std::size_t size, T&& value) noexcept // for argument constructor
	{
		Dog *ptr = (Dog*) malloc(size); // allocate the memory
		if (ptr)
		{
			::new (ptr)  Dog(std::forward<T>(value)); // pass the argument exactly as was passed to operator new,
														// using perfect forwarding
			return ptr;
		}
		else
			return nullptr;

	}


	~Dog() { std::cout << "destructor " << std::endl;  }
};



int main(void)
{
	// BUT we have to BE VERY CAREFUL when calling these member operators


	
	Dog *d = (Dog*) Dog::operator new(sizeof(Dog), "Const Char * Argument"); // argument version
	Dog *d2 = (Dog*)Dog::operator new(sizeof(Dog)); // default constructor argument

	//1 this works as expected, do what you specified in the member operator new, everything goes normal. 
	// but the syntax is longer




	Dog *d3 = new Dog(); // default constructor
	Dog *d4 = new("Const Char * Argument") Dog(); // argument constructor

	// this is shorter, goes into your member operator new, BUT when it returns to this scope,
	// call the default constructor for *d3, and for *d4 too.

	// so this ends up calling constructors twice for both objects.



}