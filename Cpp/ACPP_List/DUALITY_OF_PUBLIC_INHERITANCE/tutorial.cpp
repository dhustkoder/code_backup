#include <iostream>
#define LOG(x) std::cout << x << std::endl



/*
	The Duality of Public Inheritance

	- Inheritance of Interface
	- Inheritance of Implementation

	- Both.

*/



// When we Public Inherite from a Class, we are making a is-a Relation-ship between the classes

// It means as we know, that the Derived Class is a Kind of the Base Class.

// In is-a RelationShip the derived class should be able to do everything the base class can do (even if it does in a diferent way of course)

// Lets take a look into our abstract class Dog, 
class Dog
{
public:
	virtual void bark() = 0; // a pure virtual function, means that when we Derive from Dog,
	// we will Inherite the INTERFACE of bark, but not the IMPLEMENTATION, cuz there is no implementation
	// is pure virtual.

	void run() { LOG("I'm running"); } // this is a concrete function of Dog, it have a Implementation,
	// and it is non-virtual, which means that when using Public Inheritance, we must Inherite the 
	// INTERFACE and IMPLEMENTATION of function "run", the Derived class must not Over-Write "run",
	// to keep is-a Relation-Ship between the classes..


	

	virtual void eat() {  LOG("I'm eating"); } // a virtual function with implementation.
	// Here the Derived Classes have a choice, We can Inherite the INTERFACE only, and OVER-WRITE
	// the function in our Derived Class,
	// OR we can Inherite the INTERFACE and IMPLEMENTATION of "eat".


protected:
	void sleep() { LOG("I'm sleeping"); } // a protected non-virtual function.
	// Here the Derived Classes only Inherite the IMPLEMENTATION. and not the INTERFACE.

};


class YellowDog : public Dog
{
public:
	void bark() {  LOG("Yellow Dog's bark" << a); } // Implement the INTERFACE ONLY, that we Inherited.
	
	// keep "run", and "eat" implementations
	
	void iSleep() { this->sleep(); } 
	// Provided a Interface for sleep, function which we inherite the IMPLEMENTATION ONLY

};


// IS-A Relation-Ship (commonly Public Inheritance)


/*  C++ types:

	1. Pure-Virtual PUBLIC Function - Inherit INTERFACE Only

	2. Impure-Virtual PUBLIC Function - Inherit INTERFACE and a DEFAULT IMPLEMENTATION (can be over-written in Derived classes)


	3. Non-Virtual PUBLIC Function - Inherit INTERFACE and IMPLEMENTATION.


	4. Protected Function - Inherit IMPLEMENTATION Only

	As a software designer, it is very important to separete the concepts of INTERFACE and IMPLEMENTATION
	
	And know when to use one or the other
*/


/* INTERFACE INHERITANCE:
	benefits


	1. Subtyping
		you can use a derived type in a context that take a Base type.


	2. Polymorphism
		can change the behaviour  between  different Derived classes.




	Pitfalls:
		-- Be careful of interface bloat
			interfaces must be designed to be minimal enough.
			when inheritance is too much , may end up with a too big interface


		-- Interfaces must not reveal implementation details

*/



/* IMPLEMENTATION INHERITANCE

	- Increase code complexity
	- Not encouraged





	Guidelines for IMPLEMENTATION INHERITANCE

	1. Do not use inheritance for code reuse, Use COMPOSITION

	2. Minimize the implementation in base classes. base classes should be thin.

	3. Minimize the level of hierarchies in IMPLEMENTATION Inheritance


	

	"Inheritance is evil"  ???

	"Inheritance is often useful, but more often overused(abused)"

 	

*/


