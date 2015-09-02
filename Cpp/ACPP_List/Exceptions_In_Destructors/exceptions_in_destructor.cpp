#include <iostream>
#include <typeinfo>

class Dog
{
public:
	Dog(std::string _name) : name(_name)
	{
		std::cout << name << " is born!" << std::endl;
	}
	~Dog()
	{
		
			std::cout << name << " is destroyed!" << std::endl;
			// throw 10; this is dangerous , might throw 2 pending exceptions in the end of the try block , causing the program to terminate;
	}


/*	~Dog() // Solution 1
	{
		try{
			std::cout << name << " is destroyed!" << std::endl;
		}catch(...)
		{
			//
		}
		
		// Well this might work if you're not a client. cause if a exception is caught  in the ellipsis ( ... ) you will not known for certain what happened.
		// And your client will have silent problems in the program.

	} 
*/


	void PrepareToDestr() // Solution 2
	{
		// Clean Up
		throw 20;
	/* Solution 2 : Use a function to PREPARE the Object to be Destroyed.
	 * 	this can work. So the Client can handle the exception. 
	 *
	 * 	BUT if you have 2 PrepareToDestr(); functions for each Object if the first one throws a exception the other object will be destroyed without calling 
	 * 	its own PrepareToDestr. So it has to be used Carefully
	 * 
	 *
	 */



	
	}
private:
	const std::string name;

};




int main()
{
	try{
		Dog dog1("Barao");             /*  throwing exceptions in the destructor is not a good idea, if the objects are on stack and the catch block 
										   throws 1 exception from a normal function , before it enters the ( catch ) it will destroy the Dog that may throw
										   another exception . if that happens the program crash.
										
										*/
		Dog dog2("Pitoco");	
	}catch(int a)
	{
		std::cout << a << " is cought" << std::endl;
	}

	/*  Solution 1 : handle the exceptions in the Dog Destructor not letting exception pass 
	 *  	but it can be no good for a Client. if you're using ellipsis catch(...), for an unknown exception. It can break
	 *  	your client code silently. the client cannot handle that exception.
	 */

	/* Solution 2 : Use a function to PREPARE the Object to be Destroyed.
	 * 	this can work. So the Client can handle the exception. 
	 *
	 * 	BUT if you have 2 PrepareToDestr(); functions for each Object if the first one throws a exception the other object will be destroyed without calling 
	 * 	its own PrepareToDestr. So it has to be used Carefully
	 * 
	 *
	 */


	/* Solution 3 : Use Solution number 2 , or throw exception moderally in the destructor , BUT manage the object in the HEAP
	 *
	 * 	allocate the object in the heap with new keyword. and Destroy it carefully with a try/catch block and treat each object with it
	 *
	 */
	Dog *dog1 = new Dog("barao");
	Dog *dog2 = new Dog("Pitoco");

	try{
		dog1->PrepareToDestr();
		delete dog1;
	}catch(int x){
		std::cout << x << " exception was caught while Preaparing To Destroy dog1! " << std::endl;
		delete dog1;
	}
	
	try{
		dog2->PrepareToDestr();
		delete dog2;
	}catch(int x){
		std::cout << x << " exception was caught while Preparing To Destroy dog2! "<< std::endl;
		delete dog2;
	}






}
