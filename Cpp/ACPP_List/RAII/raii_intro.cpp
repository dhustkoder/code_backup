#include <iostream>
#include <stdexcept>
#include <string>





/* 		RAII : Resource Aquisition Is Initialization.
 *
 * 		This "paradigm" is wide spread in modern C++
 *   	
 *      We can use it to write safer code in C++ 
 *
 *      With RAII we can handle better exceptions in constructing a object, handling resources, heap allocation...
 *
 *      Smart Pointer are a good example of RAII, you allocate something in the heap when constructing a smart pointer, and the object delete it automaticaly
 *      	std::vector , std::array ... STL containers are good examples of RAII
 * 		
 * 		Lets write a RAII class to manage a array to get a better picture. 
 *
 *      There are some STEPS we have to follow to create a proper RAII class
 *
 *
 *      1 *** The Resource must be relinquished in the DESTRUCTOR ( delete pointers, close files, close connections .... )
 *
 *      2 *** The Instance of the Raii class must be STACK ALLOCATED. otherwise you will have to delete it, then it would be exception unsafe.
 *
 *      3 *** The Resource must be aquired in the CONSTRUCTOR ( allocate pointers, open files, open connections .... )
 *
 *
 *
 */



// our class
template<typename T>
class RAII_Array
{


/*  	Our class is very, very simple. it try to allocate an array of type T  , if it fails it throws an exception, if not...
 *   		you can use your array and does not need to delete it manualy.
 *
 *
 * */




public:
	RAII_Array(const size_t t_size) : heap_array ( nullptr )
	{
		
		try
		{
			heap_array = new T [ t_size ];
		}
		catch(...) // I'll use ellipis just in case that, clang++ use bad_alloc, g++ may use bad_array_new_length
		{ 	
			if( heap_array == nullptr )
				throw std::runtime_error("error trying to allocate array of size: " + std::to_string(t_size) );
		
		}
	}

	T& operator[](const size_t offset)
	{
		return heap_array [ offset ];
	}

	~RAII_Array()
	{
		delete heap_array;
	}
private:
	T *heap_array;

};

// Now lets see how using RAII is much better than not use it.



void Raii_Test()
{
	
	unsigned long long length = ~0;
	
	// Not Using RAII

	try
	{
		float *pointer = new float [ length ];
		// ... do stuff
		// UNSAFE. An exception here, means that the code jump to catch block, and the "pointer" is out of scope and not deleted. memory leak.
		delete pointer;
	
	}
	catch(...)
	{
		std::cerr << "error" << std::endl;
	
	}


	//Using RAII
	try
	{
		RAII_Array<float> array( length );
		// do things...

		// no need to delete. if exception is throw, the array is destructed and "heap_array" is deleted.

	}
	catch(std::runtime_error &err)
	{
		std::cerr << err.what() << std::endl;
	}
}



int main()
{
	

	Raii_Test();



}
