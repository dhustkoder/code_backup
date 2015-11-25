#include <iostream>



/* Define your own New-Handler

	1. what is new-handler ?

	New handler is a function invoked when operator new failed to allocate memory.
	It's purpose is to help memory allocation to succeed.

		std::set_new_handler() installs a new handler and returns the current new handler
*/


class T
{
public:
	static void *operator new(std::size_t) noexcept
	{
		pri();
	}

private:
	static void pri()
	{

	};
};

void noMoreMem()
{
	std::cout << "aborting the program" << std::endl;
	std::terminate();
}

void foo()
{
	unsigned long long *ptr = new unsigned long long[0xfffffff]; // if can't allocate this
	// noMoreMem will be called
}



/*
int main()
{
	std::set_new_handler(noMoreMem); // here we set our handler for that will be used by the global operator new
	foo(); 

}
*/