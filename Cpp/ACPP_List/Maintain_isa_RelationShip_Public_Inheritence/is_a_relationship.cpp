#include <iostream>
#include <string>
// In is-a RelationShip the derived class should be able to do everything the base class can do (even if it does in a diferent way of course)

// Wrong cause we are making the Penguin fly...
/*

class Bird {
public:
	void fly() {};
};



class Penguin : public Bird {

};
*/

// How can we fix it , if the fly function will really make a Penguin object FLY ?


// Changing the structure of the project like this
// it fix our problem and organize better, and keep the is-a relationship, cause Penguin can do all that base Bird can do 
class Bird{
public:
};

class FlyableBird : public Bird{
public:
	void fly() {};
};


class Penguin : public Bird {

};




// Anti-Polimorfism example. as we can see , in this example a derived class is over-writing a NON-VIRTUAL function. that is kind of bad.
// no, in a OOP project it can become really bad. NEVER overwrite a NON-VIRTUAL function. Why ?

class Dog {
public:
	void bark() { std::cout << "Whoof, I am  Just a dog" << std::endl;  }
};

class YellowDog : public Dog {
public:
	void bark() { std::cout << "Whoof, I am a yellowDog" << std::endl;  }
};
// lets take a  look why
void dogExample()
{
	YellowDog *py = new YellowDog(); // create a new object from a pointer

	py->bark(); // Whoof I am a yellowdog 
	// ok it worked, executed the function that we wanted.

	Dog *pd = py; // now lets pass the address of the object , to a base class pointer

	pd->Dog::bark(); // whoof I am just a dog
	// and now it brings a kind of unexpected function , the function from the base class
	// why would we want to call a base class function from a derived class that we over-writed that same function ??
	// so, it is easy to solve, using virtual keyword.. we already know that
	// now lets take a look in other problem, a problem when using virtual functions

	delete py;

}
// Lets take a look, pay attention to the default value of the parameters in the virtual function attack
class Snake {
public:
	virtual void attack(int a) { std::cout << "I attack with " << a << std::endl;  }
	virtual void attack(std::string msg = "just a") { std::cout << "I'm " << msg << " Snake!" << std::endl; }

};


class VenomSnake : public Snake {
public:
	using Snake::attack;
	virtual void attack(std::string msg = "a venom ") { std::cout << "I'm " << msg << " Snake!" << std::endl; }
};


void snakeExample()
{
	VenomSnake *pv = new VenomSnake();

	pv->attack(); // ok it worked as expected...

	// lets try the virtual function calling it from a base class pointer.

	Snake *ps = pv;

	ps->attack(10); // I'm just a snake!


	// what happened ? , our function is virtual it sould have worked, well it worked, it calls the function from VenomSnake but with 
	// the default parameter from the base class Snake. Cause the default parameters are bound in compile time to their functions

	// What can we do to prevent wrong default parameters on virtual functions ?, well ,NEVER overwrite a default parameter in virtual functions

	// Another problem that can rise in this context, is if the Snake base class have other version of attack function overloaded to take a integer parameter

	// so if we call this overloaded function attack from a VenomSnake pointer
	pv->attack(10); // yes the code dont compile.
	
	// Well, This BROKES OUR IS-A RELATIONSHIP cause now VenomSnake cant do all that Snake base class does
	// how we fix? we can over-write this version of attack in the VenomSnake class, OR if we dont want to overwrite and want to use the very same function that
	// is in Snake base class we add the keyword: using Snake::attack;
	// so the compiler will put find the overloaded version of attack when asked.

	
}

int main()
{
	//dogExample();
	snakeExample();
	std::cin.ignore();
	return 0;
}