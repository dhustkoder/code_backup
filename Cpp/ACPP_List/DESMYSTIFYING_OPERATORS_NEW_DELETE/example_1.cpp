#include <iostream>


// Desmystifing operator new/delete



class Dog
{
public:
	Dog() { std::cout << "dog constructed" << std::endl; }
};


int main(void)
{
	// What happens when the following code is executed ?

	Dog *pd = new Dog();

	// step 1. operator new is called and allocate memory for Dog

	// step 2. Dog's constructor is called to create a Dog

	// step 3. if step 2 throws exception, operator delete is called to free memory allocated in step 1



	delete pd;

	// step 1. destructor of Dog is called.

	// step 2. operator delete is called to free memory allocated for Dog;







}