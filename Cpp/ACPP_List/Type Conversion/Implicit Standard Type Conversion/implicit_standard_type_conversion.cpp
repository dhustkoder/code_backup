#include <iostream>



class BigBoss
{
public:
	BigBoss()
	{
		std::cout << "We let ourselves interfere with the times..." << std::endl; 
	}
};

class SolidSnake : public BigBoss
{
public:
	SolidSnake()
	{
		std::cout << "War has changed..." << std::endl;
	}		

};


void foo(char c)
{
	std::cout << "character c in foo: " << c << std::endl;
}

int main()
{
// Implicit Standard Conversions, are performed whenever a type T1 is used in a context that does not accept that type, but accept some other type, T2 in particular;
//
//
// The program is compiled, if there is only one ( unambiguous ) implicit conversion sequence from T1 to T2. ( if there is a type conversion for T1 to T2 to begin with )

	
	
// example 1 :
	
	char c = 'A';
	int i = c; 
	// implicit standard type conversion, the integer value of character variable c is assign to integer variable i. this is a simple conversion
	// after all, characters are no more than integer values.

	std::cout << "value of c: " << c <<  std::endl << "value of i: " << i << std::endl;

// example 2 :
	
	char *ptr = 0;
   	// this is interpreted as a null pointer, the NULL is 0; nullptr is better for use, 
	//cuz helps redability like passing parameter for a pointer rather than a integer


// obs:
	foo(65);	
	
	//this works the same for function parameters
	
// example 3 : 
	
	BigBoss* soldier = new SolidSnake; // standard pointer type conversion
	delete soldier;
	// the base class pointer, can point to its derived classes ...
}











