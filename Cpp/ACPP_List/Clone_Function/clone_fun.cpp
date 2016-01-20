#include <iostream>



// USING CLONE FUNCTION


// Supose we have 2 classes  class Dog the base , and RedDog the child;


class Dog
{
public:
	virtual void bark() const noexcept		{ std::cout <<  " Im a Dog! " << std::endl; }
};

class RedDog : public Dog
{
public:
	virtual void bark() const noexcept		{ std::cout << " Im a RedDog! " << std::endl ;}
};


// what if we want to copy-construct from any child class ? 



void foo(Dog* d) // foo's parameter is a Dog*, so it can be called with any class that have Dog as its base class
{

	Dog* c = new Dog(*d);  // here is the problem , we cant create a real RedDog ( or any child class ), if were doing = new Dog,
							// it will just create a base Dog, not a real copy of a RedDog;
							// so the output will always be " Im a Dog! "

	c->bark();

}





// So Lets resolve it in a simple way, we dont need to check the pointers with a switch or ifs and elses, for such simple task...
// so the clone function will resolve this for us. in more complex cases that we want to get the type of an object is not this case.
// this is just how to copy-construct any child class, for such functions that take a pointer to a base class, that can have a lot of child classes


// Here we have our base class BigBoss, and 2 child classes that derived from him, each one speaks their respective quotes 
class BigBoss
{
public:
	virtual void speak() { std::cout << " This is outer heaven! - Big Boss " << std::endl; }
	virtual BigBoss* clone()  { return new BigBoss(*this); }

};

class SolidSnake : public BigBoss
{
public:
	virtual void speak() { std::cout << " War has changed... - Solid Snake " << std::endl; }
	virtual SolidSnake* clone() { return new SolidSnake(*this); }
};


class LiquidSnake : public BigBoss
{
public:
	virtual void speak() { std::cout << " You enjoy all the killing... that's why! - Liquid Snake " << std::endl;}
	virtual LiquidSnake* clone() { return new LiquidSnake(*this); }
};



// this is too an axample of how virtual functions returns type can be different if they're compatible
void soldierBase(BigBoss* soldier)
{
	BigBoss *newClone = soldier->clone();

	newClone->speak();
}



int main()
{
	Dog dog;
	RedDog redDog;
	foo(&dog);
	foo(&redDog); // always a base Dog is created there.


	BigBoss *soldier[3] =
	{
		new BigBoss, new SolidSnake, new LiquidSnake
	};

	soldierBase(soldier[0]); 	 	// now it works good. each class is properly allocated.
	soldierBase(soldier[1]);
	soldierBase(soldier[2]);

	for (auto *ptr : soldier)
		delete ptr;
}
