#include <iostream>

/* STATIC_CAST: 
 *
 * static_cast can perform conversions between pointers to related classes, not only upcasts ( from pointer-to-derived TO pointer-to-base )
 * but also downcasts ( from pointer-to-base TO pointer-to-derived ). 
 *
 * ATTENTION: No checks are performed during RUN-TIME to guarantee that the object being converted is in fact a FULL object of the destination TYPE.
 *
 * Therefore it is up to the PROGRAMMER to ensure that the conversion is safe.
 * On the other side, it does not incur the overhead of the type-safety checks of dynamic_cast, that will check if types are compatible in RUN-TIME
 *
 *
 */

class Base{
public:
	virtual void iAm() { std::cout << "I'm Base!" << std::endl; }
	virtual ~Base() { std::cout << "Base destroyed" << std::endl; }
};

class Derived : public Base {
public:
	virtual void iAm() { std::cout << "I'm Derived!" << std::endl; }
	virtual ~Derived() { std::cout << "Derived destroyed" << std::endl; }
};


void dangerous_conversion()
{
	Base *base = new Base;
	Derived *derived = static_cast<Derived*>(base); // this would be valid code, although "derived", would point to an incomplete object of the class
												// and could lead to RUN-TIME errors if dereferenced.

	delete derived; // note how this will not call Derived destructor, cause is not a complete object of type Derived
}


void safe_conversion()
{
	Base *base = new Derived;
	Derived *derived = static_cast<Derived*>(base);
	// this is safe conversion, cause "base" points to a Derived type

	delete derived; // EXTRA: deleting through Derived* pointer type ensure the Derived class destructor will be called, (if destructor in base class is not declared virtual)
	// so, when using pointers and pointer casts ensure base classes destructors are declared virtual OR BECAREFUL when deleting objects.
}	


int main()
{

	dangerous_conversion();
	safe_conversion();

	/* THEREFORE --------------------------------------------------------------------------------------------------------------------------------
	 *
	 * static_cast is able to perform with pointer to classes not only the conversions allowed implicitly, but also their opposite conversions.
	 * 
	 * static_cast is also able to perform all conversions allowed implicitly (not only thise with pointer to classes),
	 * and is also able to perform the opposite of these. it can:
	 *
	 * 	* Convert from void* to any pointer type. In this case, it guarantees that if the void* value was obtained by converting from that same pointer type,
	 *		the resulting pointer value is the same.
	 *	
	 * 	* Convert integers, floating-point values and enum types to enum types.
	 *
	 *
	 * 	Additionally, static_cast can also perform the following:
	 *
	 * 		* Explicitly call a single-argument constructor or a conversion operator.
	 * 		
	 *		* Convert to rvalue references.
	 *
	 * 		* Convert enum class values. into integers or floating-point values.
	 * 		
	 *		* Convert any type to void, evaluating and discarding the value.
	 *
	 *
	 */

	 void *ptr = new Base;

	 //ptr->iAm(); // error

	 static_cast<Base*>(ptr)->iAm(); // works ok.

	 // but also can be done wrong

	 static_cast<Derived*>(ptr)->iAm(); // will give you I'm Base. but is dangerous and must be avoided.

}




























