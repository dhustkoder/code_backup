

#include <iostream>


// Uderstanding  Rvalue and Lvalue



// Why do we care?

// 1. Understand C++ construct, and decypher compiler errors and warnings

// 2. C++ 11 intruced a new feature called rvalue reference.


// 3. You want to be a good programmer. and learn everything



// SIMPLIFIED Definition

// Lvalue - An object that occupies some identifiable location in memory
// ( so something in memory , not in register)

// Rvalue - Any object that is not a Lvalue.



class Dog {
public:
	static int a;
	void bark(int assign) { a = assign; }
};
int Dog::a;
// Lvalue Examples:
void Lvalues()
{
	int i; // i is a Lvalue

	int *p = &i; // i's address (location in memory) is identifiable.

	i = 2; // 

	Dog d1; // Lvalue of  a user defined type (class)
	
	// most variables in c++ code are Lvalues
}




// Rvalue Examples:

void Rvalues()
{
	int x = 2; // 2 is an Rvalue
	
	x = x + 2; // ( x + 2 ) is an Rvalue

	//int *p = &(x + 2); // error

	//(x + 2) = 4; // error;

	Dog d1;
	d1 = Dog(); // Dog(); is an Rvalue

}



// Now lets see a little of References, When we talk about references we're defaultly talking about Lvalues references.
// well, in c++11 there are Rvalue references now, so lets be more explicit


// References - Lvalue Reference

void reference()
{
	int i;

	int &r = i;


	//int &r2 = 5; // error, cannot create a reference from Rvalue;

	// exception : const reference can be initialize with Rvalue
	const int &r3 = 5; // no error


}

// Lvalue can be used to create Rvalue
void create_Rvalue()
{

	int i = 1;

	int x = i + 2; // (i+2) Rvalue

}



// Rvalue can be use to create Lvalue
void create_Lvalue()
{
	int arr[3];

	*(arr + 2) = 20;


}



// Misconception: function or operator always yields Rvalues..
int myGlobal;
int& return_Lvalue()
{
	return myGlobal;
}

void misconception_1()
{
	return_Lvalue() = 50; // this code compiles. so the function returns a Lvalue;
}

// A more common example
void misconception_1_2()
{
	int arr[10];

	arr[2] = 10;

	// operator [] generates a Lvalue.
}



// Misconception 2: Lvalues are modifiable.

// C language: : Lvalue means "value suitable for left-hand-side of assignment"

void misconception_2()
{
	const int c = 1; // c is a Lvalue

	//c = 2; // error , c isn't suitable for left-hand-side of assignment ( not modifiable )

}



// Misconception 3: Rvalues are not modifiable.
int sum(int x , int y) { return x + y; }
void misconception_3()
{
	int i;

	//i + 3 = 6; // error ok;

	//sum(3, 4) = 7; // error ok;

	// But it is not true for user defined Types

	Dog().bark(888); // bark() may change the state of the dog object, static variables, and such

	std::cout << Dog().a << std::endl; // 888
}


int main()
{
	misconception_3();
}
