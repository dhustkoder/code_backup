#include <iostream>


// Desmystifing operator new/delete


/*  Reasons To Custumize New/Delete

	1. Usage Error Detection:
		- Memory leak detection/garbage collection.
		- array index overrun/underrun

	 2. Improve efficiency
		a. Clustering relatd objects to reduce page fault
		b. Fixed size allocation ( good for application with many small objects).
		c. Align similar size objects to same places to reduce fragmentation.

	3. Perform Additional tasks:
		a. Fill the deallocated memory withs 0's - security
		b. Collect usage statistics.

*/

/* Writing a GOOD memory manager is HARD
 *
 * Before writing your own version of new/delete, consider:
 * 
 * 1. Tweak your compiler toward your needs;
 * 2. Search for memory management library, E.g. Pool Library from Boost
*/















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