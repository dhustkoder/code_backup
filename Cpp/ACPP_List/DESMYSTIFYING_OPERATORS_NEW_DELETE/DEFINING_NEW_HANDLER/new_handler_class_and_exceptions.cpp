#include <iostream>
#define LOG(x) std::cout << x << std::endl;


class Dog
{
public:


	static void *operator new(std::size_t size) throw(std::bad_alloc)
	{
		auto originalHandler = std::set_new_handler(noMemForDog);
		void *pMemory;
		try
		{
			pMemory = ::operator new(size); // call global new,
			// if an exception is thrown the originalHandler will not be reseted.
			// so we need to ensure that
		}
		catch (std::bad_alloc& ba)
		{
			std::set_new_handler(originalHandler);// reset the originalHandler even if excpetion is thrown
			throw ba;
		}

		std::set_new_handler(originalHandler);
		return pMemory;
		
	}
private:
	unsigned long long hair[0xFFFFFFF];
	static void noMemForDog()
	{
		LOG("no more memory for dogs");
		throw std::bad_alloc();
	}

};


int main()
{
	try
	{
		Dog *p = new Dog();
		// So we have make sure that the original handler will be set again if an exception is throw by our Handler or
		// by operator new
	}
	catch (std::bad_alloc& err)
	{
		LOG("cannot allocate memory");

	}


}