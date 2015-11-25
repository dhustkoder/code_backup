#include <iostream>

// Lets introduce std::new_handler: is a function that is invoked when operator new fails to allocate memory

// std::set_new_handler : install a new handler and returns the current handler

// the default new handler is null



void *operator new(std::size_t size) throw(std::bad_alloc)
{
	while (true)
	{
		void *ptr = malloc(size); // allocate memory
		if (ptr) // if allocate succeded
			return ptr; // return allocate address

		std::new_handler handler = std::set_new_handler(nullptr); // get current handler
		std::set_new_handler(handler);

		if (handler)
			(*handler)(); // invoke the handler.
		else
			throw std::bad_alloc(); // if the handler is null, there is nothing to do and throw exception
	}


}


