#include <iostream>

/* DYNAMIC_CAST
 *
 * dynamic_cast can only be used with pointers and references to classes (or with void*). Its purpose is to ensure that the result of the type conversion
 * points to a valid complete object of the destination pointer type.
 *
 * This naturally includes pointer UPCAST (converting from pointer-to-derived TO pointer-to-base), in the same way as allowed as an implicit conversion.
 *
 * BUT dynamic_cast can also DOWNCAST  ( convert from pointer-to-base TO pointer-to-derived ) POLYMORPHIC CLASSES (those with virtual members) if -and only if-
 * the pointed object is a valid complete object of the target type. for example: 
 *
 *
 */

class Base {
public:
	virtual void dummy() { std::cout << "Base's dummy" << std::endl; }
	virtual ~Base() { std::cout << "Base destroyed" << std::endl; }
};

class Derived : public Base {
public:
	virtual void dummy() { std::cout << "Derived's dummy" << std::endl; }
	virtual ~Derived()	{ std::cout << "Derived destroyed" << std::endl; }
};

int main()
{

	try {
		Base *base = new Base;
		Base *derived = new Derived;
		

		Derived *derived2;

		derived2 = dynamic_cast<Derived*>(derived); // work ok.
		
		if( derived2 == nullptr )
			std::cout << "dynamic_cast failed" << std::endl;
		else
			derived2->dummy();

		derived2 = dynamic_cast<Derived*>(base); // doesn't work.
		
		if( derived2 == nullptr )
			std::cout << "dynamic_cast failed" << std::endl;
		else
			derived2->dummy();
	}
	catch(std::exception &error)
	{
		std::cout << error.what() << std::endl;
	}



	/* --------------------------------------------------------------------------------------------------------------------------------------------------------
	 *
	 * The code above tries to perform 2 dynamic casts from pointer objects of type Base* ( "base" and "derived" ) to a pointer of type Derived*,
	 * but only the first attempt is successful.
	 *
	 * Notice their respective initializations:
	 *  Base *base = new Base;
	 * 	Base *derived = new Derived;
	 *
	 *
	 * Even though both are pointers of type Base*, "derived" actually points to an object of type Derived, while "base" points to an object of type Base.
	 * Therefore, when their respective type-casts are performed using dynamic_cast, "derived" is pointing to a full object of class Derived, whereas "base" is
	 * pointing to an object of class Base, which is an incomplete object of class Derived
	 *
	 * 
	 *
	 *
	 */







}

































